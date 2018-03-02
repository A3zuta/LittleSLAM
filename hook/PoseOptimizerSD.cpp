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
 * @file PoseOptimizerSD.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "PoseOptimizerSD.h"

using namespace std;

////////

// �f�[�^�Ή��Â��Œ�̂��ƁA�����linitPose��^���ă��{�b�g�ʒu�̐���lestPose�����߂�
double PoseOptimizerSD::optimizePose(Pose2D &initPose, Pose2D &estPose) {
  double th = initPose.th;
  double tx = initPose.tx;
  double ty = initPose.ty;
  double txmin=tx, tymin=ty, thmin=th;         // �R�X�g�ŏ��̉�
  double evmin = HUGE_VAL;                     // �R�X�g�̍ŏ��l
  double evold = evmin;                        // 1�O�̃R�X�g�l�B��������Ɏg��

  double ev = cfunc->calValue(tx, ty, th);     // �R�X�g�v�Z
  int nn=0;                                    // �J��Ԃ��񐔁B�m�F�p
  double kk=0.00001;                           // �ŋ}�~���@�̃X�e�b�v���W��
  while (abs(evold-ev) > evthre) {             // ��������B1�O�̒l�Ƃ̕ω����������ƏI��
    nn++;
    evold = ev;

    // ���l�v�Z�ɂ��Δ���
    double dEtx = (cfunc->calValue(tx+dd, ty, th) - ev)/dd;
    double dEty = (cfunc->calValue(tx, ty+dd, th) - ev)/dd;
    double dEth = (cfunc->calValue(tx, ty, th+da) - ev)/da;

    // �����W����kk�������ăX�e�b�v���ɂ���
    double dx = -kk*dEtx;
    double dy = -kk*dEty;
    double dth = -kk*dEth;
    tx += dx;  ty += dy;  th += dth;            // �X�e�b�v���������Ď��̒T���ʒu�����߂�

    ev = cfunc->calValue(tx, ty, th);           // ���̈ʒu�ŃR�X�g�v�Z

    if (ev < evmin) {                           // ev������܂ł̍ŏ��Ȃ�X�V
      evmin = ev;
      txmin = tx;  tymin = ty;  thmin = th;
    }

//    printf("nn=%d, ev=%g, evold=%g, abs(evold-ev)=%g\n", nn, ev, evold, abs(evold-ev));         // �m�F�p
  }

  ++allN;
  if (allN > 0 && evmin < 100) 
    sum += evmin;
//  printf("allN=%d, evmin=%g, avg=%g\n", allN, evmin, (sum/allN));         // �m�F�p

//  printf("nn=%d, ev=%g\n", nn, ev);         // �m�F�p

  estPose.setVal(txmin, tymin, thmin);          // �ŏ��l��^�������ۑ�

  return(evmin);
}
