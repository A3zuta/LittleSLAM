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
 * @file ScanPointAnalyser.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef SCAN_ANALYSER_H_
#define SCAN_ANALYSER_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Scan2D.h"


class ScanPointAnalyser
{
private:
  static const double FPDMIN;               // �אړ_�Ƃ̍ŏ�����[m]�B�����菬�����ƌ덷���傫���Ȃ�̂Ŗ@���v�Z�Ɏg��Ȃ��B
  static const double FPDMAX;               // �אړ_�Ƃ̍ő勗��[m]�B������傫���ƕs�A���Ƃ݂Ȃ��Ė@���v�Z�Ɏg��Ȃ��B
  static const int CRTHRE = 45;             // �@�������ω���臒l[�x]�B������傫���ƃR�[�i�_�Ƃ݂Ȃ��B
  static const int INVALID = -1;
  double costh;                             // ���E�̖@�������̐H���Ⴂ��臒l

public:
  ScanPointAnalyser() : costh(cos(DEG2RAD(CRTHRE))) {
  }

  ~ScanPointAnalyser() {
  }

//////////
  
  void analysePoints(std::vector<LPoint2D> &lps);
  bool calNormal(int idx, const std::vector<LPoint2D> &lps, int dir, Vector2D &normal);

};

#endif

