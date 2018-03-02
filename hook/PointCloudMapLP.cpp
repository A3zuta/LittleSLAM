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
 * @file PointCloudMapLP.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "PointCloudMapLP.h"
#include "NNGridTable.h"

using namespace std;

double PointCloudMapLP::atdThre = 10;

///////////

// �i�q�e�[�u����p���āA�����n�}�̑�\�_�𓾂�
vector<LPoint2D> Submap::subsamplePoints(int nthre) {
  NNGridTable nntab;                     // �i�q�e�[�u��
  for (size_t i=0; i<mps.size(); i++) {
    LPoint2D &lp = mps[i];
    nntab.addPoint(&lp);                 // �S�_��o�^
  }

  vector<LPoint2D> sps;
  nntab.makeCellPoints(nthre, sps);      // nthre�ȏ�̃Z���̑�\�_��sps�ɓ����
  printf("mps.size=%lu, sps.size=%lu\n", mps.size(), sps.size());

  return(sps);
}

/////////

// ���{�b�g�ʒu�̒ǉ�
void PointCloudMapLP::addPose(const Pose2D &p) {
  // �ݐϑ��s����(atd)�̌v�Z
  if (poses.size() > 0) {
    Pose2D pp = poses.back();
    atd += sqrt((p.tx - pp.tx)*(p.tx - pp.tx) + (p.ty - pp.ty)*(p.ty - pp.ty));
  }
  else {
    atd += sqrt(p.tx*p.tx + p.ty*p.ty);
  }

  poses.emplace_back(p);
}

// �X�L�����_�̒ǉ�
void PointCloudMapLP::addPoints(const vector<LPoint2D> &lps) {
  Submap &curSubmap = submaps.back();              // ���݂̕����n�}
  if (atd - curSubmap.atdS >= atdThre ) {          // �ݐϑ��s������臒l�𒴂�����V���������n�}�ɕς���
    size_t size = poses.size();
    curSubmap.cntE = size-1;                       // �����n�}�̍Ō�̃X�L�����ԍ�
    curSubmap.mps = curSubmap.subsamplePoints(nthre); // �I�����������n�}�͑�\�_�݂̂ɂ���i�y�ʉ��j

    Submap submap(atd, size);                      // �V���������n�}
    submap.addPoints(lps);                         // �X�L�����_�Q�̓o�^
    submaps.emplace_back(submap);                  // �����n�}��ǉ�
  }
  else {
    curSubmap.addPoints(lps);                      // ���݂̕����n�}�ɓ_�Q��ǉ�
  }
}

// �S�̒n�}�̐����B�Ǐ��n�}�������ł�������ɍ������������
void PointCloudMapLP::makeGlobalMap(){
  globalMap.clear();                               // ������
  localMap.clear();
  // ���݈ȊO�̂��łɊm�肵�������n�}����_���W�߂�
  for (size_t i=0; i<submaps.size()-1; i++) {
    Submap &submap = submaps[i];                   // �����n�}
    vector<LPoint2D> &mps = submap.mps;            // �����n�}�̓_�Q�B��\�_�����ɂȂ��Ă���
    for (size_t j=0; j<mps.size(); j++) {
      globalMap.emplace_back(mps[j]);              // �S�̒n�}�ɂ͑S�_�����
    }
    if (i == submaps.size()-2) {                   // �Ǐ��n�}�ɂ͍Ō�̕����n�}���������
      for (size_t j=0; j<mps.size(); j++) {
        localMap.emplace_back(mps[j]);
      }
    }
  }

  // ���݂̕����n�}�̑�\�_��S�̒n�}�ƋǏ��n�}�ɓ����
  Submap &curSubmap = submaps.back();              // ���݂̕����n�}
  vector<LPoint2D> sps = curSubmap.subsamplePoints(nthre);  // ��\�_�𓾂�
  for (size_t i=0; i<sps.size(); i++) {
    globalMap.emplace_back(sps[i]);
    localMap.emplace_back(sps[i]);
  }

  // �ȉ��͊m�F�p
  printf("curSubmap.atd=%g, atd=%g, sps.size=%lu\n", curSubmap.atdS, atd, sps.size());
  printf("submaps.size=%lu, globalMap.size=%lu\n", submaps.size(), globalMap.size());
}

// �Ǐ��n�}�̐���
void PointCloudMapLP::makeLocalMap(){
  localMap.clear();                                // ������
  if (submaps.size() >= 2) {
    Submap &submap = submaps[submaps.size()-2];    // ���O�̕����n�}�����g��
    vector<LPoint2D> &mps = submap.mps;            // �����n�}�̓_�Q�B��\�_�����ɂȂ��Ă���
    for (size_t i=0; i<mps.size(); i++) {
      localMap.emplace_back(mps[i]);
    }
  }

  // ���݂̕����n�}�̑�\�_���Ǐ��n�}�ɓ����
  Submap &curSubmap = submaps.back();              // ���݂̕����n�}
  vector<LPoint2D> sps = curSubmap.subsamplePoints(nthre);  // ��\�_�𓾂�
  for (size_t i=0; i<sps.size(); i++) {
    localMap.emplace_back(sps[i]);
  }

  printf("localMap.size=%lu\n", localMap.size());   // �m�F�p
}

//////////

// �|�[�Y������̃��{�b�g�O��newPose��p���āA�n�}���č\�z����
void PointCloudMapLP::remakeMaps(const vector<Pose2D> &newPoses){
  // �e�����n�}���̓_�̈ʒu���C������
  for (size_t i=0; i<submaps.size(); i++) {
    Submap &submap = submaps[i];
    vector<LPoint2D> &mps = submap.mps;                // �����n�}�̓_�Q�B���ݒn�}�ȊO�͑�\�_�ɂȂ��Ă���
    for (size_t j=0; j<mps.size(); j++) {
      LPoint2D &mp = mps[j];
      size_t idx = mp.sid;                             // �_�̃X�L�����ԍ�
      if (idx >= poses.size()) {                       // �s���ȃX�L�����ԍ��i��������o�O�j
        continue;
      }

      const Pose2D &oldPose = poses[idx];              // mp�ɑΉ�����Â����{�b�g�ʒu
      const Pose2D &newPose = newPoses[idx];           // mp�ɑΉ�����V�������{�b�g�ʒu
      const double (*R1)[2] = oldPose.Rmat;
      const double (*R2)[2] = newPose.Rmat;
      LPoint2D lp1 = oldPose.relativePoint(mp);        // oldPose��mp���Z���T���W�n�ɕϊ�
      LPoint2D lp2 = newPose.globalPoint(lp1);         // newPose�Ń|�[�Y������̒n�}���W�n�ɕϊ�
      mp.x = lp2.x;
      mp.y = lp2.y;
      double nx = R1[0][0]*mp.nx + R1[1][0]*mp.ny;     // �@���x�N�g����oldPose�ŃZ���T���W�n�ɕϊ�
      double ny = R1[0][1]*mp.nx + R1[1][1]*mp.ny;
      double nx2 = R2[0][0]*nx + R2[0][1]*ny;          // �@���x�N�g����newPose�Ń|�[�Y������̒n�}���W�n�ɕϊ�
      double ny2 = R2[1][0]*nx + R2[1][1]*ny;
      mp.setNormal(nx2, ny2);
    }
  }

  makeGlobalMap();                                     // �����n�}����S�̒n�}�ƋǏ��n�}�𐶐�

  for (size_t i=0; i<poses.size(); i++) {              // poses���|�[�Y������̒l�ɍX�V
    poses[i] = newPoses[i];
  }
  lastPose = newPoses.back();
}
