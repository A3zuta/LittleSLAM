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
 * @file NNGridTable.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "NNGridTable.h"

using namespace std;

////////////

// �i�q�e�[�u���ɃX�L�����_lp��o�^����
void NNGridTable::addPoint(const LPoint2D *lp) {
  // �e�[�u�������̃C���f�b�N�X�v�Z�B�܂��A�Ώۗ̈���ɂ��邩�`�F�b�N����B
  int xi = static_cast<int>(lp->x/csize) + tsize;
  if (xi < 0 || xi > 2*tsize)                      // �Ώۗ̈�̊O
    return;
  int yi = static_cast<int>(lp->y/csize) + tsize;
  if (yi < 0 || yi > 2*tsize)                      // �Ώۗ̈�̊O
    return;

  size_t idx = static_cast<size_t>(yi*(2*tsize +1) + xi);   // �e�[�u���̃C���f�b�N�X
  table[idx].lps.push_back(lp);                             // �ړI�̃Z���ɓ����
}

///////////

// �X�L�����_clp��predPose�ō��W�ϊ������ʒu�ɍł��߂��_���i�q�e�[�u�����猩����
const LPoint2D *NNGridTable::findClosestPoint(const LPoint2D *clp, const Pose2D &predPose) {
  LPoint2D glp;                           // clp�̗\���ʒu
  predPose.globalPoint(*clp, glp);         // relPose�ō��W�ϊ�

  // clp�̃e�[�u���C���f�b�N�X�B�Ώۗ̈���ɂ��邩�`�F�b�N����B
  int cxi = static_cast<int>(glp.x/csize) + tsize;
  if (cxi < 0 || cxi > 2*tsize)
    return(nullptr);
  int cyi = static_cast<int>(glp.y/csize) + tsize;
  if (cyi < 0 || cyi > 2*tsize)
    return(nullptr);

  size_t pn=0;                            // �T�����Z�����̓_�̑����B�m�F�p
  double dmin=1000000;
  const LPoint2D *lpmin = nullptr;        // �ł��߂��_�i�ړI�̓_�j
  double dthre=0.2;                       // �����艓���_�͏��O����[m]
  int R=static_cast<int>(dthre/csize);

  // �}R�l����T��
  for (int i=-R; i<=R; i++) {
    int yi = cyi+i;                       // cyi����L����
    if (yi < 0 || yi > 2*tsize)
      continue;
    for (int j=-R; j<=R; j++) {
      int xi = cxi+j;                     // cxi����L����
      if (xi < 0 || xi > 2*tsize)
        continue;

      size_t idx = yi*(2*tsize+1) + xi;             // �e�[�u���C���f�b�N�X
      NNGridCell &cell = table[idx];                // ���̃Z��
      vector<const LPoint2D*> &lps = cell.lps;      // �Z�������X�L�����_�Q
      for (size_t k=0; k<lps.size(); k++) {
        const LPoint2D *lp = lps[k];
        double d = (lp->x - glp.x)*(lp->x - glp.x) + (lp->y - glp.y)*(lp->y - glp.y);

        if (d <= dthre*dthre && d < dmin) {         // dthre���ŋ������ŏ��ƂȂ�_��ۑ�
          dmin = d;
          lpmin = lp;
        }
      }
      pn += lps.size();
    }
  }
//  printf("pn=%d\n", pn);                 // �T�����Z�����̓_�̑����B�m�F�p

  return(lpmin);
}

////////////

// �i�q�e�[�u���̊e�Z���̑�\�_�������ps�Ɋi�[����B
void NNGridTable::makeCellPoints(int nthre, vector<LPoint2D> &ps) {
  // ����̓Z�����̊e�_�̃X�L�����ԍ��̕��ς��Ƃ�B
  // �X�L�����ԍ��̍ŐV�l���Ƃ�ꍇ�́A���̕����̃R�����g���͂����A
  // ���ςƂ�ꍇ�i2�s�j���R�����g�A�E�g����B

  size_t nn=0;                           // �e�[�u�����̑S�Z�����B�m�F�p
  for (size_t i=0; i<table.size(); i++) {
    vector<const LPoint2D*> &lps = table[i].lps;      // �Z���̃X�L�����_�Q
    nn += lps.size();
    if (lps.size() >= nthre) {           // �_����nthre��葽���Z��������������
      double gx=0, gy=0;                 // �_�Q�̏d�S�ʒu
      double nx=0, ny=0;                 // �_�Q�̖@���x�N�g���̕���
      int sid=0;
      for (size_t j=0; j<lps.size(); j++) {
        const LPoint2D *lp = lps[j];
        gx += lp->x;                     // �ʒu��ݐ�
        gy += lp->y;
        nx += lp->nx;                    // �@���x�N�g��������ݐ�
        ny += lp->ny;
        sid += lp->sid;                  // �X�L�����ԍ��̕��ςƂ�ꍇ
//        if (lp->sid > sid)             // �X�L�����ԍ��̍ŐV�l�Ƃ�ꍇ
//          sid = lp->sid;
//        printf("sid=%d\n", lp->sid);
      }
      gx /= lps.size();                  // ����
      gy /= lps.size();
      double L = sqrt(nx*nx + ny*ny);
      nx /=  L;                          // ���ρi���K���j
      ny /=  L;
      sid /= lps.size();                 // �X�L�����ԍ��̕��ςƂ�ꍇ

      LPoint2D newLp(sid, gx, gy);       // �Z���̑�\�_�𐶐�
      newLp.setNormal(nx, ny);           // �@���x�N�g���ݒ�
      newLp.setType(LINE);               // �^�C�v�͒����ɂ���
      ps.emplace_back(newLp);            // ps�ɒǉ�
    }
  }

//  printf("nn=%d\n", nn);               // �e�[�u�����̑S�Z�����B�m�F�p
}
