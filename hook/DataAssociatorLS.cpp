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
 * @file DataAssociatorLS.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include <boost/timer.hpp>
#include "DataAssociatorLS.h"

using namespace std;

// ���݃X�L����curScan�̊e�X�L�����_�ɑΉ�����_��baseLps���猩����
double DataAssociatorLS::findCorrespondence(const Scan2D *curScan, const Pose2D &predPose) {
  boost::timer tim;                                 // �������ԑ���p

  double dthre = 0.2;                               // �����艓���_�͏��O����[m]
  curLps.clear();                                   // �Ή��Â����݃X�L�����_�Q����ɂ���
  refLps.clear();                                   // �Ή��Â��Q�ƃX�L�����_�Q����ɂ���
  for (size_t i=0; i<curScan->lps.size(); i++) {
    const LPoint2D *clp = &(curScan->lps[i]);       // ���݃X�L�����̓_�B�|�C���^�ŁB

    // �X�L�����_lp��predPose�ō��W�ϊ������ʒu�ɍł��߂��_��������
    LPoint2D glp;                                   // clp�̗\���ʒu
    predPose.globalPoint(*clp, glp);                // predPose�ō��W�ϊ�

    double dmin = HUGE_VAL;                         // �����ŏ��l
    const LPoint2D *rlpmin = nullptr;               // �ł��߂��_
    for (size_t j=0; j<baseLps.size(); j++) {
      const LPoint2D *rlp = baseLps[j];             // �Q�ƃX�L�����_
      double d = (glp.x - rlp->x)*(glp.x - rlp->x) + (glp.y - rlp->y)*(glp.y - rlp->y);
      if (d <= dthre*dthre && d < dmin) {           // dthre���ŋ������ŏ��ƂȂ�_��ۑ�
        dmin = d;
        rlpmin = rlp;
      }
    }
    if (rlpmin != nullptr) {                        // �ŋߖT�_������Γo�^
      curLps.push_back(clp);
      refLps.push_back(rlpmin);
    }
  }
  
  double ratio = (1.0*curLps.size())/curScan->lps.size();         // �Ή����Ƃꂽ�_�̔䗦
//  printf("ratio=%g, clps.size=%lu\n", ratio, curScan->lps.size());

//  double t1 = 1000*tim.elapsed();                               // ��������
//  printf("Elapsed time: dassLS=%g\n", t1);

  return(ratio);
}
