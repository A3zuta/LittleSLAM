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
 * @file DataAssociator.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef DATA_ASSOCIATOR_H_
#define DATA_ASSOCIATOR_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"

class DataAssociator
{
public:
  std::vector<const LPoint2D*> curLps;            // �Ή����Ƃꂽ���݃X�L�����̓_�Q
  std::vector<const LPoint2D*> refLps;            // �Ή����Ƃꂽ�Q�ƃX�L�����̓_�Q

  DataAssociator() {
  }

  ~DataAssociator() {
  }

  virtual void setRefBase(const std::vector<LPoint2D> &lps) = 0;
  virtual double findCorrespondence(const Scan2D *curScan, const Pose2D &predPose) = 0;
};

#endif
