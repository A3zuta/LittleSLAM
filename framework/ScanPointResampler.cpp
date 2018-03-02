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
 * @file ScanPointResampler.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "ScanPointResampler.h"

using namespace std;

/////////

void ScanPointResampler::resamplePoints(Scan2D *scan) {
  vector<LPoint2D> &lps = scan->lps;           // �X�L�����_�Q
  if (lps.size() == 0)
    return;

  vector<LPoint2D> newLps;                     // ���T���v����̓_�Q

  dis = 0;                                     // dis�͗ݐϋ���
  LPoint2D lp = lps[0];
  LPoint2D prevLp = lp;
  LPoint2D np(lp.sid, lp.x, lp.y);
  newLps.emplace_back(np);                     // �ŏ��̓_�͓����
  for (size_t i=1; i<lps.size(); i++) {
    lp = lps[i];                               // �X�L�����_
    bool inserted=false;

    bool exist = findInterpolatePoint(lp, prevLp, np, inserted);

    if (exist) {                               // �����_������
      newLps.emplace_back(np);                 // �V�����_np������
      prevLp = np;                             // np�����O�_�ɂȂ�
      dis = 0;                                 // �ݐϋ��������Z�b�g
      if (inserted)                            // lp�̑O�ŕ�ԓ_����ꂽ�̂ŁAlp��������x���
        i--;
    }
    else
      prevLp = lp;                             // ����lp�����O�_�ɂȂ�
  }

  scan->setLps(newLps);

  printf("lps.size=%lu, newLps.size=%lu\n", lps.size(), newLps.size());    // �m�F�p
}

bool ScanPointResampler::findInterpolatePoint(const LPoint2D &cp, const LPoint2D &pp, LPoint2D &np, bool &inserted) {
  double dx = cp.x - pp.x;
  double dy = cp.y - pp.y;
  double L = sqrt(dx*dx+dy*dy);             // ���ݓ_cp�ƒ��O�_pp�̋���
  if (dis+L < dthreS) {                     // �\���ݐϋ���(dis+L)��dthreS��菬�����_�͍폜
    dis += L;                               // dis�ɉ��Z
    return(false);
  }
  else if (dis+L >= dthreL) {               // �\���ݐϋ�����dthreL���傫���_�͕�Ԃ����A���̂܂܎c��
    np.setData(cp.sid, cp.x, cp.y);
  }
  else {                                    // �\���ݐϋ�����dthreS�𒴂�����AdthreS�ɂȂ�悤�ɕ�Ԃ���
    double ratio = (dthreS-dis)/L;
    double x2 = dx*ratio + pp.x;            // �����L�΂��ċ�����dthreS�ɂȂ�ʒu
    double y2 = dy*ratio + pp.y;
    np.setData(cp.sid, x2, y2);
    inserted = true;                        // cp���O��np����ꂽ�Ƃ����t���O
  }
 
  return(true);
}

