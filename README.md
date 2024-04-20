# blackjack_cpp
用C++初步实现21点的人机竞赛。
基本毫无算法可言，全是逻辑...

SuperJacky6@2024.4

/*
已完成任务列表:

1.主程序的实现、改写与主程序封装。
2.13张扑克牌大于10的判定为10（若需要改成0.5则有浮点数要求）
3.CPU方永远不会爆庄。(2.3.3-3)
4.筹码的数量判断设定与报错。
5.中文本地化21点程序内容。
6.H键超级管理员设定。
	菜单问题选择拆分程序。已完成。
	游戏内容问题仿照cpu_hit与hit函数分别设定。已完成。
7.规则阐述与作者声明函数的实现。
8.大于10的点数改为0.5判断。
	全程序关于player和cpu的浮点属性修改。
9.要牌后可以单独增加筹码。

已知BUG列表：

1.程序内对于非法操作的判定仍是使用玩家手数，flag_legal未彻底使用。
2.手牌有极大可能相同。
	原因：random函数在传入时间戳的时候同时执行则获得同样数字。
	部分解决方案：更改13/10，用sleep延迟时间戳传入。
3.筹码溢出问题。
	已部分解决。
4.输入内容的检索问题。
5.CPU在已经超数的情况下会继续获取牌的bug
	已解决，函数改int增加返回与多层判定。
*/
