## LittleSLAM�̎g���� �iWindows�̏ꍇ�j

### (1) �֘A�\�t�g�E�F�A�̃C���X�g�[��

- Boost  
[Boost](http://www.boost.org/)���_�E�����[�h���āA�K���ȃt�H���_�ɉ𓀂��܂��B  
LiitleSLAM�ł́ABoost�̃w�b�_�t�@�C���������g�p����̂ŁA�r���h�͕K�v����܂���B

- Eigen3  
[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)��
�_�E�����[�h���āA�K���ȃt�H���_�ɉ𓀂��܂��B  
Eigen�̓w�b�_�t�@�C�������Ŏg�p���郉�C�u�����Ȃ̂ŁA�r���h�͕K�v����܂���B

- gnuplot  
[gnuplot](http://www.gnuplot.info/)���_�E�����[�h���ăC���X�g�[�����܂��B 
LittleSLAM����́AAPI�ł͂Ȃ��A���s�R�}���h�ŌĂяo���̂ŁA
Windows�̊��ϐ�Path��gnuplot�̃p�X��ݒ肵�Ă����܂��B  
���Ƃ��΁Agnuplot���t�H���_C:\gnuplot�ɃC���X�g�[�������ꍇ�A"Path=... ;C:\gnuplot\bin; ..."�Ƃ��܂��B  
�i�C���X�g�[���������Őݒ肵�Ă���邱�Ƃ�����܂��j

- CMake  
[CMake](https://cmake.org/)���_�E�����[�h���ăC���X�g�[�����܂��B

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
�����āA����zip�t�@�C����K���ȃt�H���_�ɓW�J���܂��B
�����ł́A���Ƃ��΁A"C:\abc\LittleSLAM"�ɓW�J����Ƃ��܂��B
"abc"�̓��[�U�����߂�C�ӂ̃t�H���_�ł��B
LittleSLAM-master.zip�̒���"LittleSLAM-master"�t�H���_�̉���
4�̃t�H���_��3�̃t�@�C����"C:\abc\LittleSLAM"�̉��ɃR�s�[���܂��B  
(B) git���g���āA���|�W�g����clone���܂��B  

- p2o�̓W�J   
"C:\abc\LittleSLAM"�̉���"p2o"�t�H���_���쐬���܂��B  
�O�q��p2o-master.zip�̒��̃t�@�C��"p2o.h"��"C:\abc\LittleSLAM\p2o"�̉��ɃR�s�[���܂��B  

- build�t�H���_�̍쐬  
"C:\abc\LittleSLAM"�̉���build�t�H���_���쐬���܂��B  
�����܂ł̃t�H���_�\���͈ȉ��̂悤�ɂȂ�܂��B

![�t�H���_�\��](images/folders.png)

- CMake�̎��s  
CMake(GUI)�����s���āALittleSLAM.sln�𐶐����܂��B  
�܂��A"Where is the source code"�������"Where to buid the binaries"���ɉ��}�̃t�H���_���w�肵�܂��B  
���ɁA Configure�{�^���������܂��B  
LittleSLAM�ɑ΂��ď��߂�CMake�����s����ꍇ�A���}�̂悤��C++�R���p�C���𕷂����̂ŁA
�g�p���Ă���C++�R���p�C�����w�肵�A"Use default native compliers"��I�����āAFinish�{�^���������܂��B  
�����āA������x�AConfigure�{�^���������A�Ō��Generate�{�^���������܂��B


![cmake](images/cmake.png)

- Eigen3�̎w��   
�����ACMake��Eigen3�̏ꏊ�iEIGEN3_INCLUDE_DIR�j��������ꂸ�ɃG���[���o���ꍇ�́A
���̂����ꂩ���s���āACMake���ċN������Configure��Generate����蒼���Ă��������B  
(A) Windows�̃V�X�e�����ϐ���EIGEN3_ROOT_DIR��ǉ����āA
������Eigen3��W�J�����t�H���_��ݒ肵�܂��B  
����ƁA���}�̂悤�ɁA"C:\abc\LittleSLAM"����cui, framework, hook�̊eCMakeLists.txt�̒��ŁA
EIGEN3_ROOT_DIR�Ŏw�肳�ꂽ�t�H���_��EIGEN3_INCLUDE_DIR�ɐݒ肳��܂��B  
(B) �eCMakeLists.txt��Eigen3�̃t�H���_����Őݒ肵�܂��B
���Ƃ��΁AEigen3��"C:\eigen"�ɓW�J�����ꍇ�́A���}��
$ENV{EIGEN3_ROOT_DIR}�̕�����C:\eigen�ɏ��������܂��B  

```
-- CMakeLists.txt��蔲�� --

find_package(Eigen3)  
IF(NOT EIGEN3_INCLUDE_DIR)          # Eigen3�̃p�X��������Ȃ�
  set(EIGEN3_INCLUDE_DIR $ENV{EIGEN3_ROOT_DIR})
ENDIF() 
```  

- Visual studio�̋N��  
"C:\abc\LittleSLAM\build"�̉���LittleSLAM.sln���ł��Ă���̂ŁA
������_�u���N���b�N����ƁAVisual studio���N�����܂��B

- �r���h  
���}�̂悤�ɁAVisual studio�ŁARelease, x64�i64�r�b�g�̏ꍇ�j���w�肵�ABuild���j���[����Build Solution�����s���܂��B

![cmake](images/build.png)


�r���h����������ƁA"build\cui\Release"�t�H���_�ɁA���s�t�@�C��LittleSLAM.exe����������܂��B  

![cmake](images/exefile.png)

### (3) ���s

Windows�R�}���h�v�����v�g����ȉ��̃R�}���h�ɂ��ALittleSLAM�����s���܂��B

</code></pre>
<pre><code> LittleSLAM [-so] �f�[�^�t�@�C���� [�J�n�X�L�����ԍ�]
</code></pre>

-s�I�v�V�������w�肷��ƁA�X�L������1���`�悵�܂��B�e�X�L�����`����m�F�������ꍇ��
�g���܂��B  
-o�I�v�V�������w�肷��ƁA�X�L�������I�h���g���f�[�^�ŕ��ׂ��n�}
�iSLAM�ɂ��n�}�ł͂Ȃ��j�𐶐����܂��B  
�I�v�V�����w�肪�Ȃ���΁ASLAM�����s���܂��B  
�J�n�X�L�����ԍ����w�肷��ƁA���̔ԍ��܂ŃX�L������ǂݔ�΂��Ă�����s���܂��B

��Ƃ��āA�ȉ��̃R�}���h��SLAM�����s���܂��B  
���̗�ł�"C:\abc\dataset"�t�H���_��"corridor.lsc"�Ƃ����f�[�^�t�@�C�����u����Ă��܂��B  
</code></pre>
<pre><code> C:\abc\LittleSLAM\build\cui\Release> LittleSLAM C:\abc\dataset\corridor.lsc
</code></pre>

![cmake](images/command.png)  
  
�R�}���h�����s����ƁALittleSLAM�̓t�@�C������f�[�^��ǂݍ���Œn�}����������
�\�z���Ă����܂��B���̗l�q��gnuplot�ɕ`�悳��܂��B  
�ŏI�I�ɁA���}�̂悤�Ȓn�}����������܂��B  
�������I����Ă��A�v���O�����͏I�������A�n�}�͂��̂܂ܕ\������Ă��܂��B  
�v���O�������I������ɂ�Ctrl-C�������Ă��������B


![cmake](images/result.png)


