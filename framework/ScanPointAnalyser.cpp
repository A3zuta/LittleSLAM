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
 * @file ScanPointAnalyser.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "ScanPointAnalyser.h"

using namespace std;
  
const double ScanPointAnalyser::FPDMIN = 0.06;      // ScanPointResampler.dthrS�Ƃ��炷
const double ScanPointAnalyser::FPDMAX = 1.0;

///////////

// �X�L�����_�̖@���x�N�g�������߂�B�܂��A�����A�R�[�i�A�Ǘ��̏ꍇ����������B
void ScanPointAnalyser::analysePoints(vector<LPoint2D> &lps) {
  for (int i=0; i<lps.size(); i++) {
    LPoint2D &lp = lps[i];                        // �X�L�����_
    ptype type;
    Vector2D nL, nR, normal;
    bool flagL = calNormal(i, lps, -1, nL);        // nL��lp�ƍ����̓_�ŋ��߂��@���x�N�g��
    bool flagR = calNormal(i, lps, 1, nR);         // nR��lp�ƉE���̓_�ŋ��߂��@���x�N�g��
    nR.x = -nR.x;                                 // ������nL�ƍ�����
    nR.y = -nR.y;
    if (flagL) {
      if (flagR) {                                     // ���E�����Ŗ@���x�N�g�����v�Z�\
        if (fabs(nL.x*nR.x + nL.y*nR.y) >= costh) {    // �����̖@�������s�ɋ߂�
          type = LINE;                                 // �����Ƃ݂Ȃ�
        }
        else {                                         // ���s���牓����΁A�R�[�i�_�Ƃ݂Ȃ�
          type = CORNER;
        }
        // ���E�����̖@���x�N�g���̕���
        double dx = nL.x+nR.x;
        double dy = nL.y+nR.y;
        double L = sqrt(dx*dx + dy*dy);
        normal.x = dx/L;
        normal.y = dy/L;
      }
      else {                       // ���������@���x�N�g�����Ƃ�Ȃ�����
        type = LINE;
        normal = nL;
      }
    }
    else {
      if (flagR) {                 // �E�������@���x�N�g�����Ƃ�Ȃ�����
        type = LINE;
        normal = nR;
      }
      else {                       // �����Ƃ��@���x�N�g�����Ƃ�Ȃ�����
        type = ISOLATE;            // �Ǘ��_�Ƃ݂Ȃ�
        normal.x = INVALID;
        normal.y = INVALID;
      }
    }
      
    lp.setNormal(normal.x, normal.y);
    lp.setType(type);
  }
}
  
  // ���ړ_cp�̗����̓_���Acp����dmin�ȏ�dmax�ȉ��̏ꍇ�ɁA�@�����v�Z����B
bool ScanPointAnalyser::calNormal(int idx, const vector<LPoint2D> &lps, int dir, Vector2D &normal){
  const LPoint2D &cp = lps[idx];                          // ���ړ_
  for (int i=idx+dir; i>=0 && i<lps.size(); i+=dir) {
    const LPoint2D &lp = lps[i];                          // cp��dir�i�����E�j���̓_
    double dx = lp.x - cp.x;
    double dy = lp.y - cp.y;
    double d = sqrt(dx*dx + dy*dy);
    if (d>=FPDMIN && d<=FPDMAX) {                         // cp��lp�̋���d���K�؂Ȃ�@���v�Z
      normal.x = dy/d;
      normal.y = -dx/d;
      return(true);
    }
      
    if (d > FPDMAX)                                       // ���͂�ǂ�ǂ񗣂��̂ŁA�r���ł�߂�
      break;
  }

  return(false);
}
