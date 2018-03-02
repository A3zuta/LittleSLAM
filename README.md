# LittleSLAM

## LittleSLAM�ɂ���

LittleSLAM�́ASLAM�w�K�p�v���O�����ł��B
2D���[�U�X�L���i�̃f�[�^�i�X�L�����j�ƃI�h���g���f�[�^���i�[�����t�@�C������͂��A
���{�b�g�ʒu�̋O�Ղ�2D�_�Q�n�}��gnuplot��ɏo�͂��܂��B

LittleSLAM�́A�X�L�����}�b�`���O�Ɋ�Â��ʒu�����A���[�U�X�L���i�ƃI�h���g���̃Z���T�Z���A
Graph-based SLAM�Ɋ�Â����[�v�����݂Ȃǂ̗v�f�Z�p����\������Ă��܂��B

LittleSLAM�͎Q�l����[1]�̋��ނƂ��č��ꂽ�v���O�����ł���A
�킩��₷����D�悵�ăV���v���ȃA���S���Y�����̗p���Ă��܂��B
���̂��߁A�t���X�y�b�N��SLAM�v���O�����Ɣ�ׂ�Ɛ��\�͗����܂����A
���e�̗����͂��₷���Ȃ��Ă��܂��B


## ���s��

LittleSLAM�̓v���O���~���O����C++�ŋL�q����Ă��܂��B
������m�F�������s���͉��L�̂��̂ł��B�������64�r�b�g�łł��B

| OS | C++ |
|:--:|:---:|
| Windows 7 | Visual C++ 2013 (Visual Studio Community 2013)|
| Windows 10 | Visual C++ 2015 (Visual Studio Community 2015)|
| Linux Ubuntu 14.04 LTS | gcc 4.8.4|
| Linux Ubuntu 16.04 LTS | gcc 5.4.0|

32�r�b�gOS�ł̓���m�F�͂��Ă��Ȃ��̂ŁA�K�v�ȏꍇ�͂������Ŏ����Ă��������B


## �K�v�ȃ\�t�g�E�F�A

LittleSLAM�̎��s�ɂ́A���L�̃\�t�g�E�F�A���K�v�ł��B

| �\�t�g�E�F�A | ���e | �o�[�W���� |
|:------------:|:----:|:----------:|
| Boost        | C++�ėp���C�u���� |1.58.0 |
| Eigen3       | ���`�㐔���C�u����|3.2.4 |
| gnuplot      | �O���t�`��c�[��  |5.0 |
| CMake        | �r���h�x���c�[��  |3.2.2 |
| p2o          | Graph-based SLAM�\���o|beta |

�o�[�W������LittleSLAM�̊J���Ŏg�p�������̂ł���A���m�ȏ����ł͂���܂���B
����ȏ�̃o�[�W�����ł���Βʏ�͓��삵�܂��B
����ȉ��̃o�[�W�����ł����삷��\���͂���܂��B

## �g����

- Windows�ł̎g������[������](doc/install-win.md)

- Linux�ł̎g������[������](doc/install-linux.md)

## �f�[�^�Z�b�g

�����p��6�̃f�[�^�t�@�C����p�ӂ��Ă��܂��B���\�Ɉꗗ�������܂��B
[����](https://furo.org/software/little_slam/dataset.zip)����_�E�����[�h�ł��܂��B


| �t�@�C����          | ���e         |
|:--------------------|:-------------|
| corridor.lsc        | �L���i�P�ꃋ�[�v�j |
| hall.lsc            | �L�ԁi�P�ꃋ�[�v�j |
| corridor-degene.lsc | �L���i�މ��j |
| hall-degene.lsc     | �L�ԁi�މ��j |
| corridor-loops.lsc  | �L���i���d���[�v�j |
| hall-loops.lsc      | �L�ԁi���d���[�v�j |

## �J�X�^�}�C�Y

LittleSLAM�͊w�K�p�v���O�����ł���A��{�`���炢�����̉��ǂ��o��
��������悤�ɃJ�X�^�}�C�Y�ł��܂��B  
�ڍׂ�[������](doc/customize.md)���Q�Ƃ��Ă��������B

## �Q�l����

���L�̏��Ђ�SLAM�̉�����ł��BSLAM�̈�ʓI�ȉ��������ƂƂ��ɁA
��̗�Ƃ���LittleSLAM�����ނɗp���A���̃\�[�X�R�[�h�̏ڍׂ�������Ă��܂��B

[1] �F�[���T�A�uSLAM���� -- ���{�b�g�̎��Ȉʒu����ƒn�}�\�z�̋Z�p�v�A�I�[���ЁA2018�N  

## ���C�Z���X

- LittleSLAM�́AMPL-2.0���C�Z���X�ɂ��ƂÂ��Ă��܂��B

