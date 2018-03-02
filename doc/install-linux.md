## LittleSLAM�̎g�����iLinux�̏ꍇ�j

### (1) �֘A�\�t�g�E�F�A�̃C���X�g�[��

- C++�R���p�C��(gcc)�ABoost�AEigen�ACMake, gnuplot  
�ȉ��̃R�}���h�ŁA�܂Ƃ߂ăC���X�g�[�����܂��B

</code></pre>
<pre><code> $ sudo apt-get install build-essential cmake libboost-all-dev libeigen3-dev gnuplot gnuplot-x11
</code></pre>

- p2o  
[p2o](https://github.com/furo-org/p2o)��Github�T�C�g���J���܂��B�ȉ��̂ǂ��炩�̕��@��p2o���_�E�����[�h���܂��B  
(A) Github��ʂ�"Clone or download"�{�^���������āA"Download ZIP"��I�����A
p2o-master.zip���_�E�����[�h���܂��Bzip�t�@�C���̓W�J���@�͌�q���܂��B  
(B) git���g���āA���|�W�g����clone���܂��B  

### (2) LittleSLAM�̃C���X�g�[��

- LittleSLAM�̓W�J  
[LittleSLAM](https://github.com/furo-org/LittleSLAM)��Github�T�C�g���J���܂��B
�ȉ��̂ǂ��炩�̕��@��LittleSLAM���_�E�����[�h���܂��B  
(A) Github��ʂ�"Clone or download"�{�^���������āA"Download ZIP"��I�����A
LittleSLAM-master.zip���_�E�����[�h���܂��B
�����āA����zip�t�@�C����K���ȃf�B���N�g���ɓW�J���܂��B
�����ł́A���Ƃ��΁A"\~/LittleSLAM"�ɓW�J����Ƃ��܂��B
LittleSLAM-master.zip�̒���"LittleSLAM-master"�f�B���N�g���̉���
4�̃f�B���N�g����3�̃t�@�C����"\~/LittleSLAM"�̉��ɃR�s�[���܂��B  
(B) git���g���āA���|�W�g����clone���܂��B

- p2o�̓W�J  
"\~/LittleSLAM"�̉���p2o�f�B���N�g�����쐬���܂��B  
�O�q��p2o-master.zip�̒��̃t�@�C��"p2o.h"��"\~/LittleSLAM/p2o"�ɃR�s�[���܂��B  

- build�f�B���N�g���̍쐬  
"\~/LittleSLAM"�̉���build�f�B���N�g�����쐬���܂��B  
�����܂ł̃f�B���N�g���\���͈ȉ��̂悤�ɂȂ�܂��B

![�f�B���N�g���\��](images/folders-lnx.png)

- CMake�̎��s  
�R���\�[���ŁAbuild�f�B���N�g���Ɉړ����Acmake�����s���܂��B

</code></pre>
<pre><code> ~/LittleSLAM$ cd build
</code></pre>
<pre><code> ~/LittleSLAM/build$ cmake ..
</code></pre>

���}��cmake�̎��s��������܂��B

![cmake](images/cmake-lnx.png)

���邢�́ACMake��GUI�ł��C���X�g�[�����āAWindows�̏ꍇ�Ɠ����悤��
GUI��CMake�����s���邱�Ƃ��ł��܂��B

- �r���h  
�R���\�[���ŁAbuild�f�B���N�g���ɂ�����make�����s���܂��B  
</code></pre>
<pre><code> ~/LittleSLAM/build$ make
</code></pre>
�r���h����������ƁA"\~/LittleSLAM/build/cui"�f�B���N�g���ɁA���s�t�@�C��LittleSLAM����������܂��B  

![cmake](images/exefile-lnx.png)

### (3) ���s

�ȉ��̃R�}���h�ŁALittleSLAM�����s���܂��B

</code></pre>
<pre><code> ./LittleSLAM [-so] �f�[�^�t�@�C���� [�J�n�X�L�����ԍ�]
</code></pre>

-s�I�v�V�������w�肷��ƁA�X�L������1���`�悵�܂��B�e�X�L�����`����m�F�������ꍇ��
�g���܂��B  
-o�I�v�V�������w�肷��ƁA�X�L�������I�h���g���f�[�^�ŕ��ׂ��n�}
�iSLAM�ɂ��n�}�ł͂Ȃ��j�𐶐����܂��B  
�I�v�V�����w�肪�Ȃ���΁ASLAM�����s���܂��B  
�J�n�X�L�����ԍ����w�肷��ƁA���̔ԍ��܂ŃX�L������ǂݔ�΂��Ă�����s���܂��B

��Ƃ��āA�ȉ��̃R�}���h��SLAM�����s���܂��B  
���̗�ł�"\~/LittleSLAM/dataset"�f�B���N�g����"corridor.lsc"�Ƃ����f�[�^�t�@�C�����u����Ă��܂��B  
</code></pre>
<pre><code> ~/LittleSLAM/build/cui$ ./LittleSLAM ~/LittleSLAM/dataset/corridor.lsc
</code></pre>

![cmake](images/command-lnx.png)  
  
�R�}���h�����s����ƁALittleSLAM�̓t�@�C������f�[�^��ǂݍ���Œn�}����������
�\�z���Ă����܂��B���̗l�q��gnuplot�ɕ`�悳��܂��B  
�ŏI�I�ɁA���}�̂悤�Ȓn�}����������܂��B  
�������I����Ă��A�v���O�����͏I�������A�n�}�͂��̂܂ܕ\������Ă��܂��B  
�v���O�������I������ɂ�Ctrl-C�������Ă��������B

�@
![cmake](images/result-lnx.png)
