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
 * @file PoseOptimizerSL.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include <boost/math/tools/minima.hpp>
#include "PoseOptimizerSL.h"

using namespace std;

////////

// �f�[�^�Ή��Â��Œ�̂��ƁA�����linitPose��^���ă��{�b�g�ʒu�̐���lestPose�����߂�
double PoseOptimizerSL::optimizePose(Pose2D &initPose, Pose2D &estPose) {
  double th = initPose.th;
  double tx = initPose.tx;
  double ty = initPose.ty;
  double txmin=tx, tymin=ty, thmin=th;           // �R�X�g�ŏ��̉�
  double evmin = HUGE_VAL;                       // �R�X�g�̍ŏ��l
  double evold = evmin;                          // 1�O�̃R�X�g�l�B��������Ɏg��
  Pose2D pose, dir;

  double ev = cfunc->calValue(tx, ty, th);       // �R�X�g�v�Z
  int nn=0;                                      // �J��Ԃ��񐔁B�m�F�p
  while (abs(evold-ev) > evthre) {               // ��������B�l�̕ω����������ƏI��
    nn++;
    evold = ev;

    // ���l�v�Z�ɂ��Δ���
    double dx = (cfunc->calValue(tx+dd, ty, th) - ev)/dd;
    double dy = (cfunc->calValue(tx, ty+dd, th) - ev)/dd;
    double dth = (cfunc->calValue(tx, ty, th+da) - ev)/da;
    tx += dx;  ty += dy;  th += dth;              // �������񎟂̒T���ʒu�����߂�

    // �u�����g�@�ɂ�钼���T��
    pose.tx = tx;  pose.ty = ty;  pose.th = th;   // �T���J�n�_
    dir.tx = dx;   dir.ty = dy;   dir.th = dth;   // �T������
    search(ev, pose, dir);                        // �����T�����s
    tx = pose.tx;  ty = pose.ty;  th = pose.th;   // �����T���ŋ��߂��ʒu

    ev = cfunc->calValue(tx, ty, th);             // ���߂��ʒu�ŃR�X�g�v�Z

    if (ev < evmin) {                             // �R�X�g������܂ł̍ŏ��Ȃ�X�V
      evmin = ev;
      txmin = tx;  tymin = ty;  thmin = th;
    }

//    printf("nn=%d, ev=%g, evold=%g, abs(evold-ev)=%g\n", nn, ev, evold, abs(evold-ev));         // �m�F�p
  }
  ++allN;
  if (allN > 0 && evmin < 100) 
    sum += evmin;
//  printf("allN=%d, nn=%d, evmin=%g, avg=%g, evthre=%g\n", allN, nn, evmin, (sum/allN), evthre);         // �m�F�p

//  printf("nn=%d, evmin=%g\n", nn, evmin);       // �m�F�p

  estPose.setVal(txmin, tymin, thmin);            // �ŏ��l��^�������ۑ�

  return(evmin);
}

////////// Line search ///////////

// boost���C�u�����̃u�����g�@�Œ����T�����s���B
// pose���n�_�ɁAdp�����ɂǂꂾ���i�߂΂悢���X�e�b�v����������B
double PoseOptimizerSL::search(double ev0, Pose2D &pose, Pose2D &dp) {
  int bits = numeric_limits<double>::digits;         // �T�����x
  boost::uintmax_t maxIter=40;                       // �ő�J��Ԃ��񐔁B�o���I�Ɍ��߂�
  pair<double, double> result = 
    boost::math::tools::brent_find_minima(
    [this, &pose, &dp](double tt) {return (objFunc(tt, pose, dp));},
    -2.0, 2.0, bits, maxIter);                       // �T���͈�(-2.0,2.0)

  double t = result.first;                           // ���߂�X�e�b�v��
  double v = result.second;                          // ���߂�ŏ��l

  pose.tx = pose.tx + t*dp.tx;                       // ���߂�ŏ�����pose�Ɋi�[
  pose.ty = pose.ty + t*dp.ty;
  pose.th = MyUtil::add(pose.th, t*dp.th);

  return(v);
}  

// �����T���̖ړI�֐��Btt���X�e�b�v��
double PoseOptimizerSL::objFunc(double tt, Pose2D &pose, Pose2D &dp) {
  double tx = pose.tx + tt*dp.tx;                     // pose����dp������tt�����i��
  double ty = pose.ty + tt*dp.ty;
  double th = MyUtil::add(pose.th, tt*dp.th);
  double v = cfunc->calValue(tx, ty, th);             // �R�X�g�֐��l

  return(v);
}
