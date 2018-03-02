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
 * @file PoseEstimatorICP.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include <boost/timer.hpp>
#include "PoseEstimatorICP.h"

using namespace std;

//////////////

// �����linitPose��^���āAICP�ɂ�胍�{�b�g�ʒu�̐���lestPose�����߂�
double PoseEstimatorICP::estimatePose(Pose2D &initPose, Pose2D &estPose){
  boost::timer tim;

  double evmin = HUGE_VAL;             // �R�X�g�ŏ��l�B�����l�͑傫��
  double evthre = 0.000001;            // �R�X�g�ω�臒l�B�ω��ʂ�����ȉ��Ȃ�J��Ԃ��I��
//  double evthre = 0.00000001;            // �R�X�g�ω�臒l�B�ω��ʂ�����ȉ��Ȃ�J��Ԃ��I��
  popt->setEvthre(evthre);
  popt->setEvlimit(0.2);               // evlimit�͊O��l��臒l[m]

  double ev = 0;                       // �R�X�g
  double evold = evmin;                // 1�O�̒l�B��������̂��߂Ɏg���B
  Pose2D pose = initPose;
  Pose2D poseMin = initPose;
  for (int i=0; abs(evold-ev) > evthre && i<100; i++) {           // i<100�͐U���΍�
    if (i > 0)
      evold = ev;
    double mratio = dass->findCorrespondence(curScan, pose);      // �f�[�^�Ή��Â�
    Pose2D newPose;
    popt->setPoints(dass->curLps, dass->refLps);                  // �Ή����ʂ�n��
    ev = popt->optimizePose(pose, newPose);                       // ���̑Ή��Â��ɂ����ă��{�b�g�ʒu�̍œK��
    pose = newPose;

    if (ev < evmin) {                                             // �R�X�g�ŏ����ʂ�ۑ�
      poseMin = newPose;
      evmin = ev;
    }

//    printf("dass.curLps.size=%lu, dass.refLps.size=%lu\n", dass->curLps.size(), dass->refLps.size());
//    printf("mratio=%g\n", mratio);
//    printf("i=%d: ev=%g, evold=%g\n", i, ev, evold);
  }

  pnrate = popt->getPnrate();
  usedNum = dass->curLps.size();

  estPose = poseMin;

  printf("finalError=%g, pnrate=%g\n", evmin, pnrate);
  printf("estPose:  tx=%g, ty=%g, th=%g\n", pose.tx, pose.ty, pose.th);      // �m�F�p

  double t1 = 1000*tim.elapsed();
  printf("PoseEstimatorICP: t1=%g\n", t1);                 // ��������

  if (evmin < HUGE_VAL)
    totalError += evmin;                                   // �덷���v
  totalTime += t1;                                         // �������ԍ��v
  printf("totalError=%g, totalTime=%g\n", totalError, totalTime);    // �m�F�p

  return(evmin);
}
