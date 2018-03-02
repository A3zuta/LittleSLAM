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
 * @file SlamLauncher.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef SLAM_LAUNCHER_H_
#define SLAM_LAUNCHER_H_

#include <vector>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

#include "SensorDataReader.h"
#include "PointCloudMap.h"
#include "SlamFrontEnd.h"
#include "SlamBackEnd.h"
#include "MapDrawer.h"
#include "FrameworkCustomizer.h"

/////////////

class SlamLauncher
{
private:
  int startN;                      // �J�n�X�L�����ԍ�
  int drawSkip;                    // �`��Ԋu
  bool odometryOnly;               // �I�h���g���ɂ��n�}�\�z��
  Pose2D ipose;                    // �I�h���g���n�}�\�z�̕⏕�f�[�^�B�����ʒu�̊p�x��0�ɂ���

  Pose2D lidarOffset;              // ���[�U�X�L���i�ƃ��{�b�g�̑��Έʒu

  SensorDataReader sreader;        // �t�@�C������̃Z���T�f�[�^�ǂݍ���
  PointCloudMap *pcmap;            // �_�Q�n�}
  SlamFrontEnd sfront;             // SLAM�t�����g�G���h
  MapDrawer mdrawer;               // gnuplot�ɂ��`��
  FrameworkCustomizer fcustom;     // �t���[�����[�N�̉���

public:
  SlamLauncher() : startN(0), drawSkip(10), odometryOnly(false), pcmap(nullptr) {
  }

  ~SlamLauncher() {
  }

///////////

  void setStartN(int n) {
    startN = n;
  }

  void setOdometryOnly(bool p) {
    odometryOnly = p;
  }

///////////

  void run();
  void showScans();
  void mapByOdometry(Scan2D *scan);
  bool setFilename(char *filename);
  void skipData(int num);
  void customizeFramework();
};

#endif
