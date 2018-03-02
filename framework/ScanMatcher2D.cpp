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
 * @file ScanMatcher2D.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "ScanMatcher2D.h"

using namespace std;

/////////

// �X�L�����}�b�`���O�̎��s
bool ScanMatcher2D::matchScan(Scan2D &curScan) {
  ++cnt;

  printf("----- ScanMatcher2D: cnt=%d start -----\n", cnt);

  // spres���ݒ肳��Ă���΁A�X�L�����_�Ԋu���ψꉻ����
  if (spres != nullptr)
    spres->resamplePoints(&curScan);

  // spana���ݒ肳��Ă���΁A�X�L�����_�̖@�����v�Z����
  if (spana != nullptr)
    spana->analysePoints(curScan.lps);

  // �ŏ��̃X�L�����͒P�ɒn�}�ɓ���邾��
  if (cnt == 0) {
    growMap(curScan, initPose);
    prevScan = curScan;                      // ���O�X�L�����̐ݒ�
    return(true);
  }

  // Scan�ɓ����Ă���I�h���g���l��p���Ĉړ��ʂ��v�Z����
  Pose2D odoMotion;                                                   // �I�h���g���Ɋ�Â��ړ���
  Pose2D::calRelativePose(curScan.pose, prevScan.pose, odoMotion);    // �O�X�L�����Ƃ̑��Έʒu���ړ���

  Pose2D lastPose = pcmap->getLastPose();                        // ���O�ʒu
  Pose2D predPose;                                               // �I�h���g���ɂ��\���ʒu
  Pose2D::calGlobalPose(odoMotion, lastPose, predPose);          // ���O�ʒu�Ɉړ��ʂ������ė\���ʒu�𓾂�

  const Scan2D *refScan = rsm->makeRefScan();                    // �Q�ƃX�L�����̐���
  estim->setScanPair(&curScan, refScan);                         // ICP�ɃX�L������ݒ�
  printf("curScan.size=%lu, refScan.size=%lu\n", curScan.lps.size(), refScan->lps.size());

  Pose2D estPose;                                                // ICP�ɂ�鐄��ʒu
  double score = estim->estimatePose(predPose, estPose);         // �\���ʒu�������l�ɂ���ICP�����s
  size_t usedNum = estim->getUsedNum();

  bool successful;                                               // �X�L�����}�b�`���O�ɐ����������ǂ���
  if (score <= scthre && usedNum >= nthre)                       // �X�R�A��臒l��菬������ΐ����Ƃ���
    successful = true;
  else 
    successful = false;
  printf("score=%g, usedNum=%lu, successful=%d\n", score, usedNum, successful);

  if (dgcheck) {                         // �މ��̑Ώ�������ꍇ
    if (successful) {
      Pose2D fusedPose;                       // �Z������
      Eigen::Matrix3d fusedCov;               // �Z���T�Z����̋����U
      pfu->setRefScan(refScan);
      // �Z���T�Z����pfu�ŁAICP���ʂƃI�h���g���l��Z������
      double ratio = pfu->fusePose(&curScan, estPose, odoMotion, lastPose, fusedPose, fusedCov);
      estPose = fusedPose;
      cov = fusedCov;
      printf("ratio=%g. Pose fused.\n", ratio);     // ratio�͑މ��x�B�m�F�p

      // �����U��ݐς���
      Eigen::Matrix3d covL;               // �ړ��ʂ̋����U
      CovarianceCalculator::rotateCovariance(lastPose, fusedCov, covL, true);          // �ړ��ʂ̋����U�ɕϊ�
      Eigen::Matrix3d tcov;                // �ݐό�̋����U
      CovarianceCalculator::accumulateCovariance(lastPose, estPose, totalCov, covL, tcov);
      totalCov = tcov;
    }
    else {                                   // ICP�����łȂ���΁A�I�h���g���ɂ��\���ʒu���g��
      estPose = predPose;
      pfu->calOdometryCovariance(odoMotion, lastPose, cov);       // cov�̓I�h���g�������U����
    }
  }
  else {
    if (!successful)
      estPose = predPose;
  }

  growMap(curScan, estPose);               // �n�}�ɃX�L�����_�Q��ǉ�
  prevScan = curScan;                      // ���O�X�L�����̐ݒ�

  // �m�F�p
//  printf("lastPose: tx=%g, ty=%g, th=%g\n", lastPose.tx, lastPose.ty, lastPose.th);
  printf("predPose: tx=%g, ty=%g, th=%g\n", predPose.tx, predPose.ty, predPose.th);     // �m�F�p
  printf("estPose: tx=%g, ty=%g, th=%g\n", estPose.tx, estPose.ty, estPose.th);
  printf("cov: %g, %g, %g, %g\n", totalCov(0,0), totalCov(0,1), totalCov(1,0), totalCov(1,1));
  printf("mcov: %g, %g, %g, %g\n", pfu->mcov(0,0), pfu->mcov(0,1), pfu->mcov(1,0), pfu->mcov(1,1));
  printf("ecov: %g, %g, %g, %g\n", pfu->ecov(0,0), pfu->ecov(0,1), pfu->ecov(1,0), pfu->ecov(1,1));

  // �����U�̕ۑ��i�m�F�p�j
//  PoseCov pcov(estPose, cov);
//  PoseCov pcov(estPose, totalCov);
//  PoseCov pcov(estPose, pfu->mcov);
  PoseCov pcov(estPose, pfu->ecov);
  poseCovs.emplace_back(pcov);

  // �ݐϑ��s�����̌v�Z�i�m�F�p�j
  Pose2D estMotion;                                                    // ����ړ���
  Pose2D::calRelativePose(estPose, lastPose, estMotion);
  atd += sqrt(estMotion.tx*estMotion.tx + estMotion.ty*estMotion.ty); 
  printf("atd=%g\n", atd);

  return(successful);
}

////////////////////

// ���݃X�L������ǉ����āA�n�}�𐬒�������
void ScanMatcher2D::growMap(const Scan2D &scan, const Pose2D &pose) {
  const vector<LPoint2D> &lps = scan.lps;                // �X�L�����_�Q(���{�b�g���W�n)
  const double (*R)[2] = pose.Rmat;                      // ���肵�����{�b�g�ʒu
  double tx = pose.tx;
  double ty = pose.ty;

  vector<LPoint2D> scanG;                                // �n�}���W�n�ł̓_�Q
  for(size_t i=0; i<lps.size(); i++) {
    const LPoint2D &lp = lps[i];
    if (lp.type == ISOLATE)                              // �Ǘ��_�i�@���Ȃ��j�͏��O
      continue;
    double x = R[0][0]*lp.x + R[0][1]*lp.y + tx;         // �n�}���W�n�ɕϊ�
    double y = R[1][0]*lp.x + R[1][1]*lp.y + ty;
    double nx = R[0][0]*lp.nx + R[0][1]*lp.ny;           // �@���x�N�g�����ϊ�
    double ny = R[1][0]*lp.nx + R[1][1]*lp.ny;

    LPoint2D mlp(cnt, x, y);                             // �V�K�ɓ_�𐶐�
    mlp.setNormal(nx, ny);
    mlp.setType(lp.type);
    scanG.emplace_back(mlp);                             // mlp��vector���ɃR�s�[�����
  }

  // �_�Q�n�}pcmap�ɓo�^
  pcmap->addPose(pose);
  pcmap->addPoints(scanG);
  pcmap->setLastPose(pose);
  pcmap->setLastScan(scan);          // �Q�ƃX�L�����p�ɕۑ�
  pcmap->makeLocalMap();             // �Ǐ��n�}�𐶐�
  
  printf("ScanMatcher: estPose: tx=%g, ty=%g, th=%g\n", pose.tx, pose.ty, pose.th);    // �m�F�p
}
