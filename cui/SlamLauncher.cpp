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
 * @file SlamLauncher.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include <boost/algorithm/string/predicate.hpp>
#include <boost/timer.hpp>
#include "SlamLauncher.h"
#include "ScanPointResampler.h"

using namespace std;                       // C++�W�����C�u�����̖��O��Ԃ��g��

//////////

void SlamLauncher::run() {
  mdrawer.initGnuplot();                   // gnuplot������
  mdrawer.setAspectRatio(-0.9);            // x����y���̔�i���ɂ���ƒ��g�����j
  
  size_t cnt = 0;                          // �����̘_������
  if (startN > 0)
    skipData(startN);                      // startN�܂Ńf�[�^��ǂݔ�΂�

  double totalTime=0, totalTimeDraw=0, totalTimeRead=0;
  Scan2D scan;
  bool eof = sreader.loadScan(cnt, scan);  // �t�@�C������X�L������1�ǂݍ���
  boost::timer tim;
  while(!eof) {
    if (odometryOnly) {                      // �I�h���g���ɂ��n�}�\�z�iSLAM���D��j
      if (cnt == 0) {
        ipose = scan.pose;
        ipose.calRmat();
      }
      mapByOdometry(&scan);
    }
    else 
      sfront.process(scan);                // SLAM�ɂ��n�}�\�z

    double t1 = 1000*tim.elapsed();

    if (cnt%drawSkip == 0) {               // drawSkip�����Ɍ��ʂ�`��
      mdrawer.drawMapGp(*pcmap);
    }
    double t2 = 1000*tim.elapsed();

    ++cnt;                                 // �_�������X�V
    eof = sreader.loadScan(cnt, scan);     // ���̃X�L������ǂݍ���

    double t3 = 1000*tim.elapsed();
    totalTime = t3;                        // �S�̏�������
    totalTimeDraw += (t2-t1);              // �`�掞�Ԃ̍��v
    totalTimeRead += (t3-t2);              // ���[�h���Ԃ̍��v

    printf("---- SlamLauncher: cnt=%lu ends ----\n", cnt);
  }
  sreader.closeScanFile();

  printf("Elapsed time: mapping=%g, drawing=%g, reading=%g\n", (totalTime-totalTimeDraw-totalTimeRead), totalTimeDraw, totalTimeRead);
  printf("SlamLauncher finished.\n");

  // �����I������`���ʂ��c�����߂�sleep�Ŗ������[�v�ɂ���Bctrl-C�ŏI���B
  while(true) {
#ifdef _WIN32
    Sleep(1000);                            // Windows�ł�Sleep
#elif __linux__
    usleep(1000000);                        // Linux�ł�usleep
#endif
  }
}

// �J�n����num�̃X�L�����܂œǂݔ�΂�
void SlamLauncher::skipData(int num) {
  Scan2D scan;
  bool eof = sreader.loadScan(0, scan);
  for (int i=0; !eof && i<num; i++) {       // num��ǂ݂���
    eof = sreader.loadScan(0, scan);
  }
}

///////// �I�h���g���̂��n�}�\�z //////////

void SlamLauncher::mapByOdometry(Scan2D *scan) {
//  Pose2D &pose = scan->pose;               // �X�L�����擾���̃I�h���g���ʒu
  Pose2D pose;
  Pose2D::calRelativePose(scan->pose, ipose, pose);
  vector<LPoint2D> &lps = scan->lps;       // �X�L�����_�Q
  vector<LPoint2D> glps;                   // �n�}���W�n�ł̓_�Q
  for (size_t j=0; j<lps.size(); j++) {
    LPoint2D &lp = lps[j];
    LPoint2D glp;
    pose.globalPoint(lp, glp);             // �Z���T���W�n����n�}���W�n�ɕϊ�
    glps.emplace_back(glp);
  }

  // �_�Q�n�}pcmap�Ƀf�[�^���i�[
  pcmap->addPose(pose);
  pcmap->addPoints(glps);
  pcmap->makeGlobalMap();

  printf("Odom pose: tx=%g, ty=%g, th=%g\n", pose.tx, pose.ty, pose.th);
}

////////// �X�L�����`�� ////////

void SlamLauncher::showScans() {
  mdrawer.initGnuplot();
  mdrawer.setRange(6);                     // �`��͈́B�X�L������6m�l���̏ꍇ
  mdrawer.setAspectRatio(-0.9);            // x����y���̔�i���ɂ���ƒ��g�����j

  ScanPointResampler spres;

  size_t cnt = 0;                          // �����̘_������
  if (startN > 0)
    skipData(startN);                      // startN�܂Ńf�[�^��ǂݔ�΂�

  Scan2D scan;
  bool eof = sreader.loadScan(cnt, scan);
  while(!eof) {
//    spres.resamplePoints(&scan);         // �R�����g�A�E�g�͂����΁A�X�L�����_�Ԋu���ψ�ɂ���B
 
    // �`��Ԋu��������
#ifdef _WIN32
    Sleep(100);                            // Windows�ł�Sleep
#elif __linux__
    usleep(100000);                        // Linux�ł�usleep
#endif

    mdrawer.drawScanGp(scan);              // �X�L�����`��

    printf("---- scan num=%lu ----\n", cnt);
    eof = sreader.loadScan(cnt, scan);
    ++cnt;
  }
  sreader.closeScanFile();
  printf("SlamLauncher finished.\n");
}

//////// �X�L�����ǂݍ��� /////////

bool SlamLauncher::setFilename(char *filename) {
  bool flag = sreader.openScanFile(filename);        // �t�@�C�����I�[�v��

  return(flag);
}

////////////

void SlamLauncher::customizeFramework() {
  fcustom.setSlamFrontEnd(&sfront);
  fcustom.makeFramework();
//  fcustom.customizeG();                         // �މ��̑Ώ������Ȃ�
//  fcustom.customizeH();                         // �މ��̑Ώ�������
  fcustom.customizeI();                           // ���[�v�����݂�����

  pcmap = fcustom.getPointCloudMap();           // customize�̌�ɂ�邱��
}
