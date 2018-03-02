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
 * @file PointCloudMap.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef POINT_CLOUD_MAP_H_
#define POINT_CLOUD_MAP_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"

// �_�Q�n�}�̊��N���X
class PointCloudMap
{
public:
  static const int MAX_POINT_NUM=1000000;          // globalMap�̍ő�_��

  int nthre;                                       // �i�q�e�[�u���Z���_��臒l(GT��LP�̂݁j

  std::vector<Pose2D> poses;                       // ���{�b�g�O��
  Pose2D lastPose;                                 // �Ō�ɐ��肵�����{�b�g�ʒu
  Scan2D lastScan;                                 // �Ō�ɏ��������X�L����

  std::vector<LPoint2D> globalMap;                 // �S�̒n�}�B�Ԉ�����̓_
  std::vector<LPoint2D> localMap;                  // ���݈ʒu�ߖT�̋Ǐ��n�}�B�X�L�����}�b�`���O�Ɏg��

  PointCloudMap() : nthre(1) {
    globalMap.reserve(MAX_POINT_NUM);              // �ŏ��Ɋm��
  }

  ~PointCloudMap() {
  }

///////

  void setNthre(int n) {
    nthre = n;
  }

  void setLastPose(const Pose2D &p) {
    lastPose = p;
  }

  Pose2D getLastPose() const {
    return(lastPose);
  }

  void setLastScan(const Scan2D &s) {
    lastScan = s;
  }

/////////////

  virtual void addPose(const Pose2D &p) = 0;
  virtual void addPoints(const std::vector<LPoint2D> &lps) = 0;
  virtual void makeGlobalMap() = 0;
  virtual void makeLocalMap() = 0;
  virtual void remakeMaps(const std::vector<Pose2D> &newPoses) = 0;
};

#endif
