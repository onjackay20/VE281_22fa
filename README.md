# VE281_22fa

p1的sorting有10个点TLE，全是快排，猜测是non-inplace快排太慢，应该可以把non-inplace快排当做inplace快排来写。凸包有三个点WA，看了下数据，可能是三点共线的情况出错了。

p3改了下给的public的erase函数。

p4要注意去重边，spfa判负环接floyd求最短路。
