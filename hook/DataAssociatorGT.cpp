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
 * @file DataAssociatorGT.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include <boost/timer.hpp>
#include "DataAssociatorGT.h"

using namespace std;


// ���݃X�L����curScan�̊e�X�L�����_��predPose�ō��W�ϊ������ʒu�ɍł��߂��_��������
double DataAssociatorGT::findCorrespondence(const Scan2D *curScan, const Pose2D &predPose) {
  boost::timer tim;                                 // �������ԑ���p

  curLps.clear();                                   // �Ή��Â����݃X�L�����_�Q����ɂ���
  refLps.clear();                                   // �Ή��Â��Q�ƃX�L�����_�Q����ɂ���

  for (size_t i=0; i<curScan->lps.size(); i++) {
    const LPoint2D *clp = &(curScan->lps[i]);       // ���݃X�L�����̓_�B�|�C���^�ŁB

    // �i�q�e�[�u���ɂ��ŋߖT�_�����߂�B�i�q�e�[�u�����ɋ���臒ldthre�����邱�Ƃɒ��ӁB
    const LPoint2D *rlp = nntab.findClosestPoint(clp, predPose);

    if (rlp != nullptr) {
      curLps.push_back(clp);                        // �ŋߖT�_������Γo�^
      refLps.push_back(rlp);
    }
  }

  double ratio = (1.0*curLps.size())/curScan->lps.size();         // �Ή����Ƃꂽ�_�̔䗦

//  double t1 = 1000*tim.elapsed();                   // ��������
//  printf("Elapsed time: dassGT=%g\n", t1);

  return(ratio);
}
