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
 * @file NNGridTable.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef _NN_GRID_TABLE_H_
#define _NN_GRID_TABLE_H_

#include <vector>
#include "MyUtil.h"
#include "Pose2D.h"

struct NNGridCell
{
  std::vector<const LPoint2D*> lps;         // ���̃Z���Ɋi�[���ꂽ�X�L�����_�Q

  void clear() {
    lps.clear();                            // ��ɂ���
  }
};

///////

// �i�q�e�[�u��
class NNGridTable
{
private:
  double csize;                       // �Z���T�C�Y[m]
  double rsize;                       // �Ώۗ̈�̃T�C�Y[m]�B�����`��1�ӂ̔����B
  int tsize;                          // �e�[�u���T�C�Y�̔���
  std::vector<NNGridCell> table;      // �e�[�u���{��

public:
  NNGridTable() : csize(0.05), rsize(40){            // �Z��5cm�A�Ώۗ̈�40x2m�l��
    tsize = static_cast<int>(rsize/csize);           // �e�[�u���T�C�Y�̔���
    size_t w = static_cast<int>(2*tsize+1);          // �e�[�u���T�C�Y
    table.resize(w*w);                               // �̈�m��
    clear();                                         // table�̏�����
  }

  ~NNGridTable() {
  }
  
  void clear() {
    for (size_t i=0; i<table.size(); i++)
      table[i].clear();                         // �e�Z������ɂ���
  }
  
////////////

  void addPoint(const LPoint2D *lp);
  const LPoint2D *findClosestPoint(const LPoint2D *clp, const Pose2D &predPose);
  void makeCellPoints(int nthre, std::vector<LPoint2D> &ps);
};

#endif

