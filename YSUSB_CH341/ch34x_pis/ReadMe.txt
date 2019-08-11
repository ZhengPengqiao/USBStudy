Chinese:
支持：Linux2.6.18 ~3.x
1、安装驱动：
	A、进入driver目录，执行
			# make
			# insmod ch341_pis.ko
2、执行应用测试程序
	A、进入demo目录，执行
			# make
		 产生DEMO与DEMO_GUI可执行文件。
	B、运行./DEMO，可在终端测试程序
		 运行./DEMO_GUI，可在gtk界面调试
		
English:
Support: Linux kernel 2.6.28 ~ 3.x
1、install driver
		A、get into ch34x_pis/driver, execute
				# make
				# insmod ch341_pis.ko
2、test the validity of driver
		A、 enter demo, execute
				# make
				Then, in this catalogue you can find two executable files, one: DEMO the other: DEMO_GUI.
		B、 execute DEMO
				# ./DEMO
		C、 execute DEMO_GUI
				# ./DEMO_GUI
				this depens on gtk+-2.0 lib. So ensure your system have this lib.