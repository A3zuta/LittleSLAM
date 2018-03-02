/****************************************************************************
 * LittleSLAM: 2D-Laser SLAM for educational use
 * Copyright (C) 2017-2018 Masahiro Tomono
 * Copyright (C) 2018 Future Robotics Technology Center (fuRo),
 *                    Chiba Institute of Technology.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * @file CovarianceCalculator.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "CovarianceCalculator.h"

using namespace std;

////////// ICP�ɂ�鐄��l�̋����U /////////

// ICP�ɂ�郍�{�b�g�ʒu�̐���l�̋����Ucov�����߂�B
// ����ʒupose�A���݃X�L�����_�QcurLps�A�Q�ƃX�L�����_�QrefLps
double CovarianceCalculator::calIcpCovariance(const Pose2D &pose, std::vector<const LPoint2D*> &curLps, std::vector<const LPoint2D*> &refLps, Eigen::Matrix3d &cov) {
  double tx = pose.tx;
  double ty = pose.ty;
  double th = pose.th;
  double a = DEG2RAD(th);
  vector<double> Jx;                                         // ���R�r�s���x�̗�
  vector<double> Jy;                                         // ���R�r�s���y�̗�
  vector<double> Jt;                                         // ���R�r�s���th�̗�

  for (size_t i=0; i<curLps.size(); i++) {
    const LPoint2D *clp = curLps[i];                         // ���݃X�L�����̓_
    const LPoint2D *rlp = refLps[i];                         // �Q�ƃX�L�����̓_

    if (rlp->type == ISOLATE)                                // �Ǘ��_�͏��O
      continue;

    double pd0 = calPDistance(clp, rlp, tx, ty, a);         // �R�X�g�֐��l
    double pdx = calPDistance(clp, rlp, tx+dd, ty, a);      // x�������ς����R�X�g�֐��l
    double pdy = calPDistance(clp, rlp, tx, ty+dd, a);      // y�������ς����R�X�g�֐��l
    double pdt = calPDistance(clp, rlp, tx, ty, a+da);      // th�������ς����R�X�g�֐��l

    Jx.push_back((pdx - pd0)/dd);                            // �Δ����ix�����j
    Jy.push_back((pdy - pd0)/dd);                            // �Δ����iy�����j
    Jt.push_back((pdt - pd0)/da);                            // �Δ����ith�����j
  }

  // �w�b�Z�s��̋ߎ�J^TJ�̌v�Z
  Eigen::Matrix3d hes = Eigen::Matrix3d::Zero(3,3);          // �ߎ��w�b�Z�s��B0�ŏ�����
  for (size_t i=0; i<Jx.size(); i++) {
    hes(0,0) += Jx[i]*Jx[i];
    hes(0,1) += Jx[i]*Jy[i];
    hes(0,2) += Jx[i]*Jt[i];
    hes(1,1) += Jy[i]*Jy[i];
    hes(1,2) += Jy[i]*Jt[i];
    hes(2,2) += Jt[i]*Jt[i];
  }
  // J^TJ���Ώ̍s��ł��邱�Ƃ𗘗p
  hes(1,0) = hes(0,1);
  hes(2,0) = hes(0,2);
  hes(2,1) = hes(1,2);

  // �����U�s��́i�ߎ��j�w�b�Z�s��̋t�s��
//  cov = hes.inverse();
  cov = MyUtil::svdInverse(hes);                              // SVD���g�����������悢

  double vals[2], vec1[2], vec2[2];
  double ratio = calEigen(cov, vals, vec1, vec2);            // �ŗL�l�v�Z���āA�މ���𒲂ׂ�

  // �K�v�ɉ����ċ����U�s��̃X�P�[���𒲐�����
//  double kk = 1;          // �މ��ŋɒ[�ɂ����ꍇ
  double kk = 0.1;       // �ʏ�
  cov *= kk;

  return(ratio);
}

// ����������p�����ϑ����f���̎�
double CovarianceCalculator::calPDistance(const LPoint2D *clp, const LPoint2D *rlp, double tx, double ty, double th) {
  double x = cos(th)*clp->x - sin(th)*clp->y + tx;                     // clp�𐄒�ʒu�ō��W�ϊ�
  double y = sin(th)*clp->x + cos(th)*clp->y + ty;
  double pdis = (x - rlp->x)*rlp->nx + (y - rlp->y)*rlp->ny;           // ���W�ϊ������_����rlp�ւ̐�������

  return(pdis);
}

///////// �^�����f���̌v�Z /////////

void CovarianceCalculator::calMotionCovarianceSimple(const Pose2D &motion, double dT, Eigen::Matrix3d &cov) {
  double dis = sqrt(motion.tx*motion.tx + motion.ty*motion.ty);   // �ړ�����
  double vt = dis/dT;                    // ���i���x[m/s]
  double wt = DEG2RAD(motion.th)/dT;     // �p���x[rad/s]
  double vthre = 0.02;                   // vt�̉����l�B���������0�ɂȂ�ꍇ�̑Ώ�
  double wthre = 0.05;                   // wt�̉����l

  if (vt < vthre)
    vt = vthre;
  if (wt < wthre)
    wt = wthre;

  double dx = vt;
  double dy = vt;
  double da = wt;

  Eigen::Matrix3d C1;
  C1.setZero();                          // �Ίp�v�f���������
  C1(0,0) = 0.001*dx*dx;                 // ���i����x
  C1(1,1) = 0.005*dy*dy;                 // ���i����y
//  C1(2,2) = 0.005*da*da;                 // ��]����
  C1(2,2) = 0.05*da*da;                 // ��]����

  // �X�P�[������
//  double kk = 100;                     // �I�h���g���̂��ꂪ�傫���ꍇ
  double kk = 1;                         // �ʏ�
  cov = kk*C1;

  // �m�F�p
  printf("calMotionCovarianceSimple\n");
  printf("vt=%g, wt=%g\n", vt, wt);
  double vals[2], vec1[2], vec2[2];
  calEigen(cov, vals, vec1, vec2);
  printf("cov : %g %g %g %g %g %g\n", cov(0,0), cov(0,1), cov(0,2), cov(1,1), cov(1,2), cov(2,2));
}

///////// �^�����f���̌v�Z /////////

// 1�t���[�����̑��s�ɂ��덷�BdT��1�t���[���̎��ԁBmotion�͂��̊Ԃ̈ړ��ʁB
void CovarianceCalculator::calMotionCovariance(double th, double dx, double dy, double dth, double dt, Eigen::Matrix3d &cov, bool accum) {
  setAlpha(1, 5);
  double dis = sqrt(dx*dx + dy*dy);   // ���s����
  double vt = dis/dt;                 // ���i���x[m/s]
  double wt = dth/dt;                 // �p���x[rad/s]
  double vthre = 0.001;               // vt�̉����l�B�^�C�~���O�ɂ��0�ɂȂ�̂�h���B
  double wthre = 0.01;                // wt�̉����l
  if (vt < vthre)
    vt = vthre;
  if (wt < wthre)
    wt = wthre;

 // �ݐς���ꍇ�́A����t-1�̋����U�s��sigma����A����t�̋����U�s����v�Z
  Eigen::Matrix3d A = Eigen::Matrix3d::Zero(3,3);
  if (accum) {
    Eigen::Matrix3d Jxk;
    calJxk(th, vt, dt, Jxk);
    A = Jxk*cov*Jxk.transpose();
  }

  Eigen::Matrix2d Uk;
  calUk(vt, wt, Uk);

  Eigen::Matrix<double, 3, 2> Juk;
  calJuk(th, dt, Juk);
  Eigen::Matrix3d B = Juk*Uk*Juk.transpose();

  cov = A + B;

}

//////////////////////////////////

void CovarianceCalculator::calUk(double vt, double wt, Eigen::Matrix2d &Uk) {
  Uk << a1*vt*vt, 0,
        0, a2*wt*wt;
}

// ���{�b�g�p���Ɋւ��郄�R�r�s��Bvt�̓��{�b�g�̑��x�Ath�̓��{�b�g�̕���(���W�A��)�Adt�͎���
void CovarianceCalculator::calJxk(double th, double vt, double dt, Eigen::Matrix3d &Jxk) {
  double cs = cos(th);
  double sn = sin(th);
  Jxk << 1, 0, -vt*dt*sn,
         0, 1, vt*dt*cs,
         0, 0, 1;
}

// 
void CovarianceCalculator::calJuk(double th, double dt, Eigen::Matrix<double, 3, 2> &Juk) {
  double cs = cos(th);
  double sn = sin(th);
  Juk << dt*cs, 0,
         dt*sn, 0,
         0, dt;
}

////////////////

// �����U�s��cov�̕��i�����������ŗL�l�������A�ŗL�l��vals�ɁA�ŗL�x�N�g����vec1��vec2�ɓ����B
double CovarianceCalculator::calEigen(const Eigen::Matrix3d &cov, double *vals, double *vec1, double *vec2) {
  // ���i�����������o��
  double cv2[2][2];
  for (int i=0; i<2; i++) 
    for (int j=0; j<2; j++) 
      cv2[i][j] = cov(i,j);

  MyUtil::calEigen2D(cv2, vals, vec1, vec2);        // �ŗL�l����
  double ratio = vals[0]/vals[1];

  // �m�F�p
  printf("Eigen: ratio=%g, val1=%g, val2=%g\n", ratio, vals[0], vals[1]);
  printf("Eigen: vec1=(%g, %g), ang=%g\n", vec1[0], vec1[1], RAD2DEG(atan2(vec1[1], vec1[0])));

  return(ratio);
}

//////////////

// �����U�s��̗ݐρB�O��ʒu�̋����U�s��prevCov�Ɉړ��ʂ̋����U�s��mcov�������āA���݈ʒu�̋����U�s��curCov�����߂�B
void CovarianceCalculator::accumulateCovariance(const Pose2D &curPose, const Pose2D &prevPose, const Eigen::Matrix3d &prevCov, const Eigen::Matrix3d &mcov, Eigen::Matrix3d &curCov) {
  Eigen::Matrix3d J1, J2;
  J1 << 1, 0, -(curPose.ty - prevPose.ty),
        0, 1, curPose.tx - prevPose.tx,
        0, 0, 1;

  double prevCos = cos(DEG2RAD(prevPose.th));
  double prevSin = sin(DEG2RAD(prevPose.th));
  J2 << prevCos, -prevSin, 0,
        prevSin, prevCos, 0,
        0, 0, 1;

  curCov = J1*prevCov*J1.transpose() + J2*mcov*J2.transpose();
}

/////////////

// �����U�s��cov��pose�̊p�x��������]������
void CovarianceCalculator::rotateCovariance(const Pose2D &pose, const Eigen::Matrix3d &cov, Eigen::Matrix3d &icov, bool reverse) {
  double cs = cos(DEG2RAD(pose.th));            // pose�̉�]����th�ɂ��cos
  double sn = sin(DEG2RAD(pose.th));
  Eigen::Matrix3d J;                            // ��]�̃��R�r�s��
  J << cs, -sn, 0,
       sn, cs, 0,
       0, 0, 1;

  Eigen::Matrix3d JT = J.transpose();

  if (reverse)
    icov = JT*cov*J;                              // �t��]�ϊ�
  else
    icov = J*cov*JT;                              // ��]�ϊ�
}
