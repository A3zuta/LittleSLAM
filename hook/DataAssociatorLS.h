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
 * @file DataAssociatorLS.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef DATA_ASSOCIATOR_LS_H_
#define DATA_ASSOCIATOR_LS_H_

#include "DataAssociator.h"

// ���`�T����p���āA���݃X�L�����ƎQ�ƃX�L�����Ԃ̓_�̑Ή��Â����s��
class DataAssociatorLS : public DataAssociator
{
private:
  std::vector<const LPoint2D*> baseLps;              // �Q�ƃX�L�����̓_���i�[���Ă����B��Ɨp

public:
  DataAssociatorLS() {
  }

  ~DataAssociatorLS() {
  }

  // �Q�ƃX�L�����̓_rlps���|�C���^�ɂ���baseLps�ɓ����
  virtual void setRefBase(const std::vector<LPoint2D> &rlps) {
    baseLps.clear();
    for (size_t i=0; i<rlps.size(); i++)
      baseLps.push_back(&rlps[i]);                // �|�C���^�ɂ��Ċi�[
  }

/////////

  virtual double findCorrespondence(const Scan2D *curScan, const Pose2D &predPose);
};

#endif
