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
 * @file Pose2D.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "Pose2D.h"

// �O���[�o�����W�n�ł̓_p���A�����iPose2D�j�̋Ǐ����W�n�ɕϊ�
LPoint2D Pose2D::relativePoint(const LPoint2D &p) const {
  double dx = p.x - tx;
  double dy = p.y - ty;
  double x = dx*Rmat[0][0] + dy*Rmat[1][0];  // ��]�̋t�s��
  double y = dx*Rmat[0][1] + dy*Rmat[1][1];
  return LPoint2D(p.sid, x, y);
}

////////

// �����iPose2D�j�̋Ǐ����W�n�ł̓_p���A�O���[�o�����W�n�ɕϊ�
LPoint2D Pose2D::globalPoint(const LPoint2D &p) const {
  double x = Rmat[0][0]*p.x + Rmat[0][1]*p.y + tx;
  double y = Rmat[1][0]*p.x + Rmat[1][1]*p.y + ty;
  return LPoint2D(p.sid, x, y);
}

// �����iPose2D�j�̋Ǐ����W�n�ł̓_p���A�O���[�o�����W�n�ɕϊ�����po�ɓ����
void Pose2D::globalPoint(const LPoint2D &pi, LPoint2D &po) const {
  po.x = Rmat[0][0]*pi.x + Rmat[0][1]*pi.y + tx;
  po.y = Rmat[1][0]*pi.x + Rmat[1][1]*pi.y + ty;
}

///////

// ����W�nbpose���猩�������W�nnpose�̑��ΈʒurelPose�����߂�iInverse compounding operator�j
void Pose2D::calRelativePose(const Pose2D &npose, const Pose2D &bpose, Pose2D &relPose) {
  const double (*R0)[2] = bpose.Rmat;           // ����W�n
  const double (*R1)[2] = npose.Rmat;           // �����W�n
  double (*R2)[2] = relPose.Rmat;               // ���Έʒu

  // ���i
  double dx = npose.tx - bpose.tx;
  double dy = npose.ty - bpose.ty;
  relPose.tx = R0[0][0]*dx + R0[1][0]*dy;
  relPose.ty = R0[0][1]*dx + R0[1][1]*dy;

  // ��]
  double th = npose.th - bpose.th;
  if (th < -180)
    th += 360;
  else if (th >= 180)
    th -= 360;
  relPose.th = th;

  relPose.calRmat();
}

// ����W�nbpose���瑊�ΈʒurelPose�����i�񂾁A���W�nnpose�����߂�iCompounding operator�j
void Pose2D::calGlobalPose(const Pose2D &relPose, const Pose2D &bpose, Pose2D &npose) {
  const double (*R0)[2] = bpose.Rmat;           // ����W�n
  const double (*R1)[2] = relPose.Rmat;         // ���Έʒu
  double (*R2)[2] = npose.Rmat;                 // �V���W�n

  // ���i
  double tx = relPose.tx;
  double ty = relPose.ty;
  npose.tx =  R0[0][0]*tx + R0[0][1]*ty + bpose.tx;
  npose.ty =  R0[1][0]*tx + R0[1][1]*ty + bpose.ty;

  // �p�x
  double th = bpose.th + relPose.th;
  if (th < -180)
    th += 360;
  else if (th >= 180)
    th -= 360;
  npose.th = th;

  npose.calRmat();
}
