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
 * @file PoseEstimatorICP.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef _POSEESTIMATOR_ICP_H_
#define _POSEESTIMATOR_ICP_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"
#include "PoseOptimizer.h"
#include "DataAssociator.h"

//////

class PoseEstimatorICP
{
private:
  const Scan2D *curScan;       // ���݃X�L����
  size_t usedNum;              // ICP�Ɏg��ꂽ�_���BLoopDetector�ŐM�����`�F�b�N�Ɏg��
  double pnrate;               // �������Ή��Â����ꂽ�_�̔䗦
  
  PoseOptimizer *popt;         // �œK���N���X
  DataAssociator *dass;        // �f�[�^�Ή��Â��N���X

public:
  double totalError;           // �덷���v
  double totalTime;            // �������ԍ��v

public:

  PoseEstimatorICP() : usedNum(0), pnrate(0), totalError(0), totalTime(0) {
  }

  ~PoseEstimatorICP() {
  }

///////

  void setPoseOptimizer(PoseOptimizer *p) {
    popt = p;
  }

  void setDataAssociator(DataAssociator *d) {
    dass = d;
  }
     
  double getPnrate() {
    return(pnrate);
  }

  size_t getUsedNum() {
    return(usedNum);
  }
  
  void setScanPair(const Scan2D *c, const Scan2D *r) {
    curScan = c;
    dass->setRefBase(r->lps);           // �f�[�^�Ή��Â��̂��߂ɎQ�ƃX�L�����_��o�^
  }

  void setScanPair(const Scan2D *c, const std::vector<LPoint2D> &refLps) {
    curScan = c;
    dass->setRefBase(refLps);           // �f�[�^�Ή��Â��̂��߂ɎQ�ƃX�L�����_��o�^
  }

////////////

  double estimatePose(Pose2D &initPose, Pose2D &estPose);
};

#endif
