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
 * @file PointCloudMapBS.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "PointCloudMapBS.h"

using namespace std;

///////////

// ���{�b�g�ʒu�̒ǉ�
void PointCloudMapBS::addPose(const Pose2D &p) {
  poses.emplace_back(p);
}

// �X�L�����_�Q�̒ǉ�
void PointCloudMapBS::addPoints(const vector<LPoint2D> &lps) {
  int skip=5;                                       // �������ɏd���̂ŁA1/5�ɊԈ���
//  int skip=10;                                       // �������ɏd���̂ŁA1/10�ɊԈ���
  for (size_t i=0; i<lps.size(); i+=skip) {
    globalMap.emplace_back(lps[i]);                 // �S�̒n�}�ɒǉ����邾��
  }
}

// �S�̒n�}�����B���łɂł��Ă���̂ŉ������Ȃ�
void PointCloudMapBS::makeGlobalMap(){
  printf("globalMap.size=%lu\n", globalMap.size());   // �m�F�p
}

// �Ǐ��n�}�����B�_�~�[
void PointCloudMapBS::makeLocalMap(){
//  localMap = globalMap;
}

////////

// �_�~�[
void PointCloudMapBS::remakeMaps(const vector<Pose2D> &newPoses) {
}
