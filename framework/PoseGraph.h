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
 * @file PoseGraph.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef POSE_GRAPH_H_
#define POSE_GRAPH_H_

#include <vector>
#include "MyUtil.h"
#include "Pose2D.h"

struct PoseArc;

/////////

// �|�[�Y�O���t�̒��_
struct PoseNode
{
  int nid;                       // �m�[�hID�BPoseGraph��nodes�̃C���f�b�N�X�i�ʂ��ԍ��j
  Pose2D pose;                   // ���̃m�[�h�̃��{�b�g�ʒu
  std::vector<PoseArc*> arcs;    // ���̃m�[�h�ɂȂ���A�[�N

  PoseNode(): nid(-1) {
  }

  PoseNode(const Pose2D &p) : nid(-1) {
    pose = p;
  }

  ~PoseNode() {
  }

//////

  void init() {
    nid = -1;
    arcs.clear();
  }

  void setPose(const Pose2D &p) {
    pose = p;
  }
  
  void setNid(int n) {
    nid = n;
  }

  void addArc(PoseArc *a) {
    arcs.push_back(a);
  }

};

////////

// �|�[�Y�O���t�̕�
struct PoseArc
{
  PoseNode *src;                      // ���̃A�[�N�̎n�_���̃m�[�h
  PoseNode *dst;                      // ���̃A�[�N�̏I�_���̃m�[�h
  Pose2D relPose;                     // ���̃A�[�N�̂����Έʒu(�v���l)
  Eigen::Matrix3d inf;                // ���s��

  PoseArc(void) : src(nullptr), dst(nullptr){
  }

  PoseArc(PoseNode *s, PoseNode *d, Pose2D &rel, const Eigen::Matrix3d _inf) {
    setup(s, d, rel, _inf);
  }
  
  ~PoseArc(void) {
  }

/////////

  void setup(PoseNode *s, PoseNode *d, const Pose2D &rel, const Eigen::Matrix3d _inf) {
    src = s;
    dst = d;
    relPose = rel;
    inf = _inf;
  }

};

////////// �|�[�Y�O���t //////////

class PoseGraph
{
private:
  static const int POOL_SIZE=100000;
  std::vector<PoseNode> nodePool;     // �m�[�h�����p�̃������v�[��
  std::vector<PoseArc> arcPool;       // �A�[�N�����p�̃������v�[��

public:
  std::vector<PoseNode*> nodes;       // �m�[�h�̏W��
  std::vector<PoseArc*> arcs;         // �A�[�N�̏W���B�A�[�N�͕Е����݂̂���

  PoseGraph() {
    nodePool.reserve(POOL_SIZE);      // �������v�[���̗̈���ŏ��Ɋm�ہBvector�̓T�C�Y���ς��ƒ��g���ړ�����̂ł������Ȃ��Ɗ댯
    arcPool.reserve(POOL_SIZE);
  }

  ~PoseGraph() {
  }
  
//////////////
  
  void reset() {
    nodes.clear();
    arcs.clear();
    nodePool.clear();
    arcPool.clear();
  }

  // �m�[�h�̐���
  PoseNode *allocNode() {
    if (nodePool.size() >= POOL_SIZE) {
      printf("Error: exceeds nodePool capacity\n");
      return(nullptr);
    }
   
    PoseNode node;
    nodePool.emplace_back(node);      // �������v�[���ɒǉ����āA������Q�Ƃ���B
    return(&(nodePool.back()));
  }

  // �A�[�N�̐���
  PoseArc *allocArc() {
    if (arcPool.size() >= POOL_SIZE) {
      printf("Error: exceeds arcPool capacity\n");
      return(nullptr);
    }

    PoseArc arc;
    arcPool.emplace_back(arc);       // �������v�[���ɒǉ����āA������Q�Ƃ���B
    return(&(arcPool.back()));
  }

//////////////

  PoseNode *addNode(const Pose2D &pose);
  void addNode(PoseNode *n1, const Pose2D &pose);
  PoseNode *findNode(int nid);

  void addArc(PoseArc *arc);
  PoseArc *makeArc(int srcNid, int dstNid, const Pose2D &relPose, const Eigen::Matrix3d &cov);
  PoseArc *findArc(int srcNid, int dstNid);

  void printNodes();
  void printArcs();

};

#endif
