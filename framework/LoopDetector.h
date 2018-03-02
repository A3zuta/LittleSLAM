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
 * @file LoopDetector.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef LOOP_DETECTOR_H_
#define LOOP_DETECTOR_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"
#include "PoseGraph.h"

///////

// ���[�v�A�[�N�ݒ���
struct LoopInfo
{
  bool arcked;                   // ���łɃ|�[�Y�A�[�N�𒣂�����
  int curId;                     // ���݃L�[�t���[��id�i�X�L�����j
  int refId;                     // �Q�ƃL�[�t���[��id�i�X�L�����C�܂��́CLocalGridMap2D�j
  Pose2D pose;                   // ���݃L�[�t���[�����Q�ƃL�[�t���[���Ƀ}�b�`����O���[�o���p���iGrid�x�[�X�̏ꍇ�͋t�j
  double score;                  // ICP�}�b�`���O�X�R�A
  Eigen::Matrix3d cov;           // �����U

  LoopInfo() : arcked(false), curId(-1), refId(-1), score(-1) {
  }

  ~LoopInfo() {
  }
  
  void setArcked(bool t) {
    arcked = t;
  }
};

//////////////

// �f�o�b�O�p�f�[�^
struct LoopMatch
{
  Scan2D curScan;
  Scan2D refScan;
  LoopInfo info;

  LoopMatch() {
  }

  LoopMatch(Scan2D &cs, Scan2D &rs, LoopInfo &i) {
    curScan = cs;
    refScan = rs;
    info = i;
  }
};

////////////

class LoopDetector
{
protected:  
  PoseGraph *pg;                               // �|�[�Y�O���t
  std::vector<LoopMatch> loopMatches;          // �f�o�b�O�p

public:
  LoopDetector() {
  }

  ~LoopDetector() {
  }

////////

  // �f�o�b�O�p
  std::vector<LoopMatch> &getLoopMatches() {
    return(loopMatches);
  }

  void setPoseGraph(PoseGraph *p) {
    pg = p;
  }

///////

  virtual bool detectLoop(Scan2D *curScan, Pose2D &curPose, int cnt);

};

#endif
