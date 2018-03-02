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
 * @file MapDrawer.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "MapDrawer.h"

using namespace std;

////////// Gnuplot�ɂ��n�}�`�� //////////

// �n�}�ƋO�Ղ�`��
void MapDrawer::drawMapGp(const PointCloudMap &pcmap) {
  const vector<LPoint2D> &lps = pcmap.globalMap;         // �n�}�̓_�Q
  const vector<Pose2D> &poses = pcmap.poses;             // ���{�b�g�O��
  drawGp(lps, poses);
}

// �X�L����1��`��
void MapDrawer::drawScanGp(const Scan2D &scan) {
  vector<Pose2D> poses;
  Pose2D pose;                   // ���_
  poses.emplace_back(pose);      // drawGp���g�����߂�vector�ɓ����
  drawGp(scan.lps, poses);
}

// ���{�b�g�O�Ղ�����`��
void MapDrawer::drawTrajectoryGp(const vector<Pose2D> &poses) {
  vector<LPoint2D> lps;          // drawGp���g�����߂̃_�~�[�i��j
  drawGp(lps, poses);
}

//////////

void MapDrawer::drawGp(const vector<LPoint2D> &lps, const vector<Pose2D> &poses, bool flush) {
  printf("drawGp: lps.size=%lu\n", lps.size());     // �_���̊m�F�p

  // gnuplot�ݒ�
  fprintf(gp, "set multiplot\n");
//  fprintf(gp, "plot '-' w p pt 7 ps 0.1, '-' with vector\n");
  fprintf(gp, "plot '-' w p pt 7 ps 0.1 lc rgb 0x0, '-' with vector\n");

  // �_�Q�̕`��
  int step1=1;                  // �_�̊Ԉ����Ԋu�B�`�悪�d���Ƃ��傫������
  for (size_t i=0; i<lps.size(); i+=step1) {
    const LPoint2D &lp = lps[i];
    fprintf(gp, "%lf %lf\n", lp.x, lp.y);    // �_�̕`��
  }
  fprintf(gp, "e\n");

  // ���{�b�g�O�Ղ̕`��
  int step2=10;                      // ���{�b�g�ʒu�̊Ԉ����Ԋu
  for (size_t i=0; i<poses.size(); i+=step2) {
    const Pose2D &pose = poses[i];
    double cx = pose.tx;             // ���i�ʒu
    double cy = pose.ty;
    double cs = pose.Rmat[0][0];     // ��]�p�ɂ��cos
    double sn = pose.Rmat[1][0];     // ��]�p�ɂ��sin

    // ���{�b�g���W�n�̈ʒu�ƌ�����`��
    double dd = 0.4;
    double x1 = cs*dd;              // ���{�b�g���W�n��x��
    double y1 = sn*dd;
    double x2 = -sn*dd;             // ���{�b�g���W�n��y��
    double y2 = cs*dd;
    fprintf(gp, "%lf %lf %lf %lf\n", cx, cy, x1, y1);
    fprintf(gp, "%lf %lf %lf %lf\n", cx, cy, x2, y2);
  }
  fprintf(gp, "e\n");

  if (flush)
    fflush(gp);         // �o�b�t�@�̃f�[�^�������o���B���ꂵ�Ȃ��ƕ`�悪�悭�Ȃ�
}
