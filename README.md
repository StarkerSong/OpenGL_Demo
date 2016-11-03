# OpenGL_Demo


## 初始化窗体 ##

### glutInitDisplayMode()函数 ###

**函数功能:**设置显示方式;

**函数原型:**void glutInitDisplayMode(unsigned int mode);

mode参数是一个GLUT库里预定义的可能的布尔组合。可以使用mode去指定**颜色模式，缓冲区**类型。

![](http://i.imgur.com/zLfxrPr.png)

 
**RGBA和INDEX(像素索引)**

 **RGB色彩模式:**是工业界的一种颜色标准，是通过对红(R)、绿(G)、蓝(B)三个颜色通道的变化以及它们相互之间的叠加来得到各式各样的颜色。

 **INDEX色彩模式:**采用一个颜色表存放并索引图像中的颜色。如果原图像中的一种颜色没有出现在查照表中，程序会选取已有颜色中最相近的颜色或使用已有颜色模拟该种颜色。能减小文件大小，同时保持视觉上的品质不变。 

**单缓冲区或双缓冲区窗口**

GLUT_SINGLE:单缓冲区窗口,当不需要用户交互时用单缓冲，需要用户交互时要用双缓冲。

GLUT_DOUBLE:双缓冲区窗口,这是产生流畅动画必须选的。Glut使用双缓冲只需要在显示回调函数中使用函数glutSwapBuffers()取代glFlush()。


### glClear()与glClearColor()函数 ###

**缓冲区种类**

``` cpp
  缓冲区                  名称
颜色缓冲区           GL_COLOR_BUFFER_BIT    　　　　　　　　　　//也就是帧缓冲区（FRAME_BUFFER）,你需要渲染的场景最终每一个像素都要写入该缓冲区,然后由它在渲染到屏幕上显示
深度缓冲区           GL_DEPTH_BUFFER_BIT　　　　　　　　　　　　//与帧缓冲区对应,用于记录上面每个像素的深度值,通过深度缓冲区,我们可以进行深度测试,从而确定像素的遮挡关系,保证渲染正确。
累积缓冲区           GL_ACCUM_BUFFER_BIT　　　　　　　　　　　　//累积缓存也存储RGBA颜色数据, 将一系列的图像合成一幅图像.
模板缓冲区           GL_STENCIM_BUFFER_BIT　　　　　　　　　　 //与深度缓冲大小相同,通过设置模版缓冲每个像素的值,我们可以指定在渲染的时候只渲染某些像素,从而可以达到一些特殊的效果
```


## 参考资料 ##

- 《OpenGL编程指南》
- [开启openGL学习之旅](http://www.cnblogs.com/MenAngel/category/843909.html)