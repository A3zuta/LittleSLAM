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
 * @file SensorDataReader.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "SensorDataReader.h"

using namespace std;

// �t�@�C������X�L������1�ǂ�
bool SensorDataReader::loadScan(size_t cnt, Scan2D &scan) {
  bool isScan=false;
  while (!inFile.eof() && !isScan) {     // �X�L������ǂނ܂ő�����
    isScan = loadLaserScan(cnt, scan);
  }

  if (isScan) 
    return(false);                       // �܂��t�@�C���������Ƃ����Ӗ�
  else
    return(true);                        // �t�@�C�����I������Ƃ����Ӗ�
}

//////////////

// �t�@�C�����獀��1��ǂށB�ǂ񂾍��ڂ��X�L�����Ȃ�true��Ԃ��B
bool SensorDataReader::loadLaserScan(size_t cnt, Scan2D &scan) {
  string type;                           // �t�@�C�����̍��ڃ��x��
  inFile >> type;
  if (type == "LASERSCAN") {             // �X�L�����̏ꍇ
    scan.setSid(cnt);

    int sid, sec, nsec;
    inFile >> sid >> sec >> nsec;        // �����͎g��Ȃ�

    vector<LPoint2D> lps;
    int pnum;                            // �X�L�����_��
    inFile >> pnum;
    lps.reserve(pnum);
    for (int i=0; i<pnum; i++) {
      float angle, range;
      inFile >> angle >> range;          // �X�L�����_�̕��ʂƋ���
      angle += angleOffset;              // ���[�U�X�L���i�̕����I�t�Z�b�g���l��
      if (range <= Scan2D::MIN_SCAN_RANGE || range >= Scan2D::MAX_SCAN_RANGE) {
//      if (range <= Scan2D::MIN_SCAN_RANGE || range >= 3.5) {         // �킴�Ƒމ����N�����₷��
        continue;
      }

      LPoint2D lp;
      lp.setSid(cnt);                    // �X�L�����ԍ���cnt�i�ʂ��ԍ��j�ɂ���
      lp.calXY(range, angle);            // angle,range����_�̈ʒuxy���v�Z
      lps.emplace_back(lp);
    }
    scan.setLps(lps);

    // �X�L�����ɑΉ�����I�h���g�����
    Pose2D &pose = scan.pose;
    inFile >> pose.tx >> pose.ty;
    double th;
    inFile >> th;
    pose.setAngle(RAD2DEG(th));          // �I�h���g���p�x�̓��W�A���Ȃ̂œx�ɂ���
    pose.calRmat();

    return(true);
  }
  else {                                 // �X�L�����ȊO�̏ꍇ
    string line;
    getline(inFile, line);               // �ǂݔ�΂�

    return(false);
  }
}
