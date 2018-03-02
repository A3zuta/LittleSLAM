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
 * @file PointCloudMapGT.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "PointCloudMapGT.h"

using namespace std;

///////////

// ���{�b�g�ʒu�̒ǉ�
void PointCloudMapGT::addPose(const Pose2D &p) {
  poses.emplace_back(p);
}

// �i�q�e�[�u���̊e�Z���̑�\�_�����߂�sps�Ɋi�[����
void PointCloudMapGT::subsamplePoints(vector<LPoint2D> &sps) {
  nntab.clear();                            // �i�q�e�[�u���̏�����
  for (size_t i=0; i<allLps.size(); i++) 
    nntab.addPoint(&(allLps[i]));           // �S�_���i�q�e�[�u���ɓo�^

  nntab.makeCellPoints(nthre, sps);         // nthre�_�ȏ゠��Z�������\�_�𓾂�

  printf("allLps.size=%lu, sps.size=%lu\n", allLps.size(), sps.size());  // �m�F�p
}

/////////

// �X�L�����_�Q��ǉ�
void PointCloudMapGT::addPoints(const vector<LPoint2D> &lps) {
  for (size_t i=0; i<lps.size(); i++)
    allLps.emplace_back(lps[i]);
}

// �S�̒n�}�̐���
void PointCloudMapGT::makeGlobalMap(){
  globalMap.clear();
  subsamplePoints(globalMap);         // �i�q�e�[�u���̊e�Z���̑�\�_����S�̒n�}�����

  printf("GT: globalMap.size=%lu\n", globalMap.size());    // �m�F�p
}

// �Ǐ��n�}�̐����B�S�̒n�}�����̂܂܎g��
void PointCloudMapGT::makeLocalMap(){
  localMap = globalMap;
  printf("GT: localMap.size=%lu\n", localMap.size());
}

////////

// �_�~�[
void PointCloudMapGT::remakeMaps(const vector<Pose2D> &newPoses) {
}
