## 一.关于项目

| 项目                 | 内容                                                         |
| :------------------- | :----------------------------------------------------------- |
| 这个作业属于哪个课程 | [2020计算机学院软件工程(罗杰 任健)](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ) |
| 这个作业的要求在哪里 | [结队项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10466) |
| **教学班级**         | 006                                                          |
| **项目地址**         | [结队项目作业](https://github.com/abTaoTao/Pair_project_git.git) |

## 二.关于GUI

* GUI可执行文件命名为intersect.exe，所需要的动态链接库为dll_Test.dll。可执行保存在文件gui_bin中，GUI源代码保存在gui_src中。

* GUI的使用方法:

  * 界面如下图：

    ![image-20200324115000456](C:\Users\太极熊\AppData\Roaming\Typora\typora-user-images\image-20200324115000456.png)

  * 手动添加图形：

    * 可以通过图形类型来选择你想添加的图形类型，然后在下方的text_box中填入坐标，注意输入的坐标是整数。然后点击添加图形，如果你添加的图形没有重复，那么会在右边的列表中列出你添加的几何对象；反之，则会报错。你可以在右边列表中选择你想要删除的图形，然后点击删除选中图形即可；清空列表顾名思义就是清空你目前添加的所有几何图形。然后点击开始绘制，就可以得到答案或者得到相应的异常提示，并绘制图像。

    * 例：![image-20200324115440255](C:\Users\太极熊\AppData\Roaming\Typora\typora-user-images\image-20200324115440255.png)

      ![image-20200324115506169](C:\Users\太极熊\AppData\Roaming\Typora\typora-user-images\image-20200324115506169.png)

  * 从文件导入：

    * 点击浏览，选择你想添加的几何对象集合文件。同样可以进行删除某个集合对象或者清空之。然后点击开始绘制，就可以得到答案或者得到相应的异常提示，并绘制图像。类似上图。

  * 附：当输入的几何对象过多的时候，可以得到答案，但是绘制图像会报异常。
  
  * **结果保存在./points.pair中**

