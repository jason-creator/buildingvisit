1.#include<iostream>  
2.#include<string>  
3.#include <stack>  
4.#include <queue>  
5.using namespace std;  
6.struct Edge  
7.{  
8.    int length; //路径的长度  
9.    int start;  //路径起点  
10.    int target; //路径终点  
11.};  
12.  
13.struct Node  
14.{  
15.    string name;            //建筑名字  
16.    string description;     //建筑信息描述  
17.    int location_x;         //建筑坐标 x 值  
18.    int location_y;         //建筑坐标 y 值  
19.};  
20.  
21.struct Graph  
22.{  
23.    struct Node * building[14];   
24.    struct Edge * road[14][14];        
25.    string direction[14][14];     //存储方向信息  
26.    bool known[14];               //判断该建筑是否被遍历  
27.};  
28.  
29.void searching (string searchname, Graph map);    
30.int translate(string name, Graph map, int flag_1);  
31.void buildingvisit(Graph map);  
32.void DFS(Graph map, int * stack, int start, int target, int top, int num, int & mark, int * sum, int temp[][14]);  
33.void shortestway(Graph map);  
34.void MergeSort (int arr [], int low, int high, int start);  
35.void Merge(int arr[], int low, int mid, int high, int start);  
36.  
37.int main()  
38.{  
39.    //初始化地图  
40.    Graph map;  
41.    for (int i = 0; i < 14; i++)  
42.    {  
43.        map.building[i] = new Node;  
44.        for (int j = 0; j < 14; j++)  
45.        {  
46.            map.road[i][j] = new Edge;  
47.            map.road[i][j]->length = 666; //非路径设置成无穷  
48.        }  
49.        map.road[i][i]->length = 0;       //到本身设置成0  
50.    }  
51.  
52.    map.road[0][1]->length = 3;//E to D  
53.  
54.    map.road[1][0]->length = 3;//D to E  
55.    map.road[1][2]->length = 2;//D to F  
56.    map.road[1][12]->length = 8;//D to canteen2  
57.  
58.    map.road[2][3]->length = 3;//F to C  
59.    map.road[2][1]->length = 2;//F to D  
60.    map.road[2][4]->length = 5;//F to A  
61.  
62.    map.road[3][2]->length = 3;//C to F  
63.  
64.    map.road[4][5]->length = 2;//A to B  
65.    map.road[4][6]->length = 5;//A to G  
66.    map.road[4][13]->length = 8;//A to canteen1  
67.    map.road[4][2]->length = 5;//A to F  
68.  
69.    map.road[5][4]->length = 2;//B to A  
70.    map.road[5][6]->length = 4;//B to G  
71.  
72.    map.road[6][4]->length = 5;//G to A  
73.    map.road[6][5]->length = 4;//G to B  
74.    map.road[6][7]->length = 6;//G to K  
75.      
76.    map.road[7][6]->length = 6;//K to G  
77.    map.road[7][8]->length = 3;//K to J  
78.    map.road[7][9]->length = 6;//K to H  
79.  
80.    map.road[8][7]->length = 3;//J to K  
81.    map.road[8][9]->length = 2;//J to H  
82.    map.road[8][10]->length = 6;//J to canteen4  
83.  
84.    map.road[9][7]->length = 6;//H to k  
85.    map.road[9][8]->length = 2;//H to J  
86.    map.road[9][10]->length = 8;//H to canteen4  
87.  
88.    map.road[10][8]->length = 6;//canteen4 to J  
89.    map.road[10][9]->length = 8;//canteen4 to H  
90.    map.road[10][11]->length = 4;//canteen4 to canteen3  
91.  
92.    map.road[11][10]->length = 4;//canteen3 to canteen4  
93.    map.road[11][13]->length = 6;//canteen3 to canteen1  
94.  
95.    map.road[13][11]->length = 6;//canteen1 to canteen3  
96.    map.road[13][12]->length = 4;//canteen1 to canteen2  
97.    map.road[13][4]->length = 8;//canteen1 to A  
98.  
99.    map.road[12][13]->length = 4;//canteen2 to canteen1  
100.    map.road[12][1]->length = 8;//canteen2 to D  
101.  
102.    //inser information  
103.    map.building[0]->name = "E building";  
104.    map.building[0]->description = "水木楼";  
105.    map.building[0]->location_x = 4;  
106.    map.building[0]->location_y = 18;  
107.  
108.    map.building[1]->name = "D building";  
109.    map.building[1]->description = "材科楼";  
110.    map.building[1]->location_x = 7;  
111.    map.building[1]->location_y = 18;  
112.  
113.    map.building[2]->name = "F building";  
114.    map.building[2]->description = "学术楼";  
115.    map.building[2]->location_x = 9;  
116.    map.building[2]->location_y = 18;  
117.  
118.    map.building[3]->name = "C building";  
119.    map.building[3]->description = "机电楼";  
120.    map.building[3]->location_x = 12;  
121.    map.building[3]->location_y = 18;  
122.  
123.    map.building[4]->name = "A building";  
124.    map.building[4]->description = "教学楼";  
125.    map.building[4]->location_x = 13;  
126.    map.building[4]->location_y = 16;  
127.  
128.    map.building[5]->name = "B building";  
129.    map.building[5]->description = "社科楼";  
130.    map.building[5]->location_x = 15;  
131.    map.building[5]->location_y = 16;  
132.  
133.    map.building[6]->name = "G building";  
134.    map.building[6]->description = "理学楼";  
135.    map.building[6]->location_x = 17;  
136.    map.building[6]->location_y = 14;  
137.  
138.    map.building[7]->name = "K building";  
139.    map.building[7]->description = "实训楼";  
140.    map.building[7]->location_x = 22;  
141.    map.building[7]->location_y = 12;   
142.  
143.    map.building[8]->name = "J building";  
144.    map.building[8]->description = "活动中心";  
145.    map.building[8]->location_x = 22;  
146.    map.building[8]->location_y = 9;  
147.  
148.    map.building[9]->name = "H building";  
149.    map.building[9]->description = "主楼";  
150.    map.building[9]->location_x = 24;  
151.    map.building[9]->location_y = 8;  
152.  
153.    map.building[10]->name = "canteen_No.4";  
154.    map.building[10]->description = "四食堂，尚未开业";  
155.    map.building[10]->location_x = 17;  
156.    map.building[10]->location_y = 6;  
157.  
158.    map.building[11]->name = "canteen_No.3";  
159.    map.building[11]->description = "三食堂，快乐食间";  
160.    map.building[11]->location_x = 14;  
161.    map.building[11]->location_y = 5;    
162.  
163.    map.building[12]->name = "canteen_No.2";  
164.    map.building[12]->description = "二食堂，三层食堂";  
165.    map.building[12]->location_x = 6;  
166.    map.building[12]->location_y = 10;    
167.  
168.    map.building[13]->name = "canteen_No.1";  
169.    map.building[13]->description = "一食堂，传统食堂";  
170.    map.building[13]->location_x = 10;  
171.    map.building[13]->location_y = 9;    
172.  
173.    //insert direction  
174.    map.direction[0][1] = "0 度方向，距离3"; //E to D  
175.  
176.    map.direction[1][0] = "180 度方向，距离3";//D to E  
177.    map.direction[1][2] = "0 度方向，距离2";//D to F  
178.    map.direction[1][12] = "-90 度方向，距离8";//D to canteen2  
179.  
180.    map.direction[2][3] = "0 度方向，距离3";//F to C  
181.    map.direction[2][1] = "180 度方向，距离2";//F to D  
182.    map.direction[2][4] = "-30 度方向，距离5";//F to A  
183.  
184.    map.direction[3][2] = "-180 度方向，距离3";//C to F  
185.  
186.    map.direction[4][5] = "0 度方向，距离2";//A to B  
187.    map.direction[4][6] = "-30 度方向，距离5";//A to G  
188.    map.direction[4][13] = "-120 度方向，距离8";//A to canteen1  
189.    map.direction[4][2] = "-150 度方向，距离5";//A to F  
190.  
191.    map.direction[5][4] = "-180 度方向，距离2";//B to A  
192.    map.direction[5][6] = "-60 度方向，距离4";//B to G  
193.  
194.    map.direction[6][4] = "-150 度方向，距离5";//G to A  
195.    map.direction[6][5] = "-120 度方向，距离4";//G to B  
196.    map.direction[6][7] = "-30 度方向，距离6";//G to K  
197.      
198.    map.direction[7][6] = "150 度方向，距离6";//K to G  
199.    map.direction[7][8] = "-90 度方向，距离3";//K to J  
200.    map.direction[7][9] = "-60 度方向，距离6";//K to H  
201.  
202.    map.direction[8][7] = "90 度方向，距离3";//J to K  
203.    map.direction[8][9] = "-60 度方向，距离2";//J to H  
204.    map.direction[8][10] = "-150 度方向，距离6";//J to canteen4  
205.  
206.    map.direction[9][7] = "-60 度方向，距离6";//H to k  
207.    map.direction[9][8] = "-120 度方向，距离2";//H to J  
208.    map.direction[9][10] = "-150 度方向，距离8";//H to canteen4  
209.  
210.    map.direction[10][8] = "60 度方向，距离6";//canteen4 to J  
211.    map.direction[10][9] = "30 度方向，距离8";//canteen4 to H  
212.    map.direction[10][11] = "-150 度方向，距离4";//canteen4 to canteen3  
213.  
214.    map.direction[11][10] = "30 度方向，距离4";//canteen3 to canteen4  
215.    map.direction[11][13] = "120 度方向，距离6";//canteen3 to canteen1  
216.  
217.    map.direction[13][11] = "-60 度方向，距离6";//canteen1 to canteen3  
218.    map.direction[13][12] = "150 度方向，距离4";//canteen1 to canteen2  
219.    map.direction[13][4] = "60 度方向，距离8";//canteen1 to A  
220.  
221.    map.direction[12][13] = "-30 度方向，距离4";//canteen2 to canteen1  
222.    map.direction[12][1] = "90 度方向，距离8";//canteen2 to D  
223.  
224.    //输入选项卡  
225.    while (1)   //死循环，除非用户自行选择退出  
226.    {  
227.    cout << "What do you want to do? （input the number）" << endl;  
228.    cout <<"1. information searching     2. building visit plan" << endl;  
229.    cout <<"3. shortest way searching    4. quit" << endl;  
230.    int choice;  
231.    string searchname;  
232.    cout << "your input is: ";  
233.    cin >> choice;                  //将选项存在choice中  
234.    switch (choice)  
235.    {  
236.    case 1:  
237.        searching(searchname, map); //信息查询函数，对应作业要求3  
238.        cout << endl;  
239.        continue;  
240.    case 2:  
241.        buildingvisit(map);         //最佳访问路径函数，对应作业要求4  
242.        cout << endl;  
243.        continue;  
244.    case 3:  
245.        shortestway(map);           //任意点路径排序，对应作业要求5  
246.        cout << endl;  
247.        continue;  
248.    default:  
249.        break;                      //退出  
250.    }  
251.    break;  
252.    }  
253.    cout << "closing......";  
254.    cin.clear();   
255.    cin.sync();  
256.    cin.get();  
257.}  
258.  
259.void searching (string searchname, Graph map)   //信息查询函数  
260.{  
261.    cout << "searching: " ;  
262.    cin >> searchname;  
263.    int len_S = searchname.size();              //获得查询内容的大小              
264.    string t = searchname;                      //将查询内容放在t中  
265.                                                //再将查找的内容与有内容进行对比  
266.    int flag_null = 1;  
267.    for (int i = 0; i < 14; i++)  
268.    {  
269.        string B = map.building[i]->name;       //将所有建筑名字信息内容放在B中  
270.        int len_B = B.size();                   //获得建筑名字的大小  
271.        if (B.find(t) != string::npos)          //在B中查找所需内容，若没有则不打印  
272.        {  
273.            cout << map.building[i]->name << ", " << map.building[i]->description << ", "   
274.                 << "location:(" << map.building[i]->location_x << ","   
275.                 << map.building[i]->location_y << ")" << endl ;  
276.        }  
277.        else   
278.        {  
279.            flag_null++;                        //计数没有查找到的建筑数量  
280.        }  
281.        while (flag_null == 15)                 //如果14个建筑都没有查到，打印相关信息  
282.        {  
283.            cout << "no relevant information" << endl;  
284.            break;  
285.        }  
286.    }  
287.}  
288.  
289.int translate(string name, Graph map, int flag_1)
290.//该函数用于用户输入名字后的转义    
291.{                           //将英文名字转译成数字，便于数组中使用  
292.    int flag_null = 1;    //控制输入的名字是否合法，是否能够找到对应数字  
293.    int flag_2 = 0;       //控制输入的名字是否精确，只允许每次输入找到一个对应建筑
294.    int j;                                          //返回名字对应的数字编号  
295.  
296.    for (int i = 0; i < 14; i++)                    //查找方法类似于搜索方法  
297.    {  
298.        string B = map.building[i]->name;  
299.        int len_B = B.size();  
300.        if (B.find(name) != string::npos)  
301.        {  
302.            j = i;  
303.            flag_2++;  
304.        }  
305.        else   
306.        {  
307.            flag_null++;  
308.        }  
309.        while (flag_null == 15)  
310.        {  
311.            cout << "no matched name!" << endl;  
312.            return -1;  
313.        }  
314.    }  
315.    if (flag_2 > 1)  
316.    {  
317.        cout << "too many matched names! please input accurate name!" << endl;
318.        return -1;  
319.    }  
320.    return j;  
321.}  
322.  
323.  
324.void buildingvisit(Graph map)                               //最佳访问路径函数  
325.{  
326.    int start, target, num, w;                                        
327.    string start_name, target_name;   
328.    int flag_1 = 0;                         //是否合法输入的标志  
329.    int flag_2 = 0;                         //两者建筑之间的景点数量是否合法的标志
330.    while (flag_1 == 0)                                               
331.    {  
332.    flag_1 = 1;  
333.    cout << "\ninput the start building and target building:";  
334.    cin >> start_name >> target_name;  
335.    start = translate(start_name, map, flag_1);            //转义名字到数字  
336.    target = translate(target_name, map, flag_1);  
337.    while (start < 0 || start > 13 || target < 0 || start >13)  
338.    {  
339.        flag_1 = 0;  
340.        break;  
341.    }  
342.    }  
343.    cout << "\ninput the number of buildings you want to visit:";  
344.    cin >> num;                                                //经历的景点数量  
345.    int top = 0;  
346.    int mark = 0;  
347.    for (int v = 0; v < 14; v++)  
348.    {  
349.        map.known[v] = false;                           //标记该建筑是否被遍历  
350.    }  
351.    int * stack = new int [14];                       //用于表示建筑序号  
352.    int temp[14][14];                                  //用于存储建筑序号信息  
353.    int * sum = new int [14];                        //用于存储每次路径的距离总和
354.    for (int i = 0; i < 14; i++)                      //初始化temp  
355.    {  
356.        for (int j = 0; j < 14; j++)  
357.        {  
358.            temp[i][j] = -1;  
359.        }  
360.    }  
361.    for (int i = 0; i < 14; i++)  
362.    {  
363.        sum[i] = 666;                                     //初始化路径和  
364.    }  
365.    DFS(map, stack, start, target, top, num, mark, sum, temp); //深度优先搜索
366.  
367.    for (int i = 0; i < num - 1; i++)  
368.    {  
369.        if (temp[0][i] < 0 || temp[0][i] > 13)  
370.        {  
371.            flag_2 = 1;  
372.            cout << "If you want to visit " << num << " buildings, "   
373.                 << "No proper way to " ;  
374.            break;  
375.        }  
376.        cout << map.building[temp[0][i]]->name << "->" ;  
377.    }  
378.    cout << map.building[target]->name << endl;  
379.  
380.    while (flag_2 == 0)  
381.    {  
382.        for ( w = 0; w + 1 < num - 1; w++)  
383.        {  
384.            cout << "\n" << map.building[temp[0][w+1]]->name << " 位于 "  
385.                << map.building[temp[0][w]]->name << " 的"  
386.                << map.direction[temp[0][w]][temp[0][w+1]];  
387.        }  
388.            cout << "\n" << map.building[target]->name << " 位于 "  
389.                << map.building[temp[0][w]]->name << " 的"  
390.                << map.direction[temp[0][w]][target];  
391.            cout << endl;  
392.            break;  
393.    }  
394.}  
395.  
396.void DFS(Graph map, int * stack, int start, int target, int top, int num, int &mark, int * sum, int temp[][14])  
397.{  
398.    int i, j, a, b, c;  
399.    stack[top++] = start;                          //首先将起点数字放入stack中  
400.    map.known[start] = true;                      //设置起点已经被访问  
401.    //开始设置从起点出发，到临近的任意一点  
402.    //若该距离<666，则证明可以走，走过之后标记true  
403.    //继续以新的一个点作为基础，往新点周边的点扩散，直到周围无未走过的点  
404.    //回溯上一个点，选择周边的另外一个点，重复此过程  
405.    //在深度优先搜索过程中，若下一个点为目标点  
406.    //则判断经历过几条路径，若经历的路径数目符合要求  
407.    //则将该建筑信息存储在temp[mark][]中，再计算该路径的和，mark++  
408.    //若出现第二条合理路径，则再将建筑信息存入temp[mark][]中，同样计算路径和  
409.    //将两个路径和进行比较，将小的放入temp[0][]中  
410.    //最后得到temp[0][]，即最短路径的建筑序号信息                             
411.    for (i = 0; i < 14; i++)                              
412.    {  
413.        if (map.road[start][i]->length < 666)  
414.        {  
415.           if (i == target)  
416.           {  
417.               while (top == num - 1)  
418.               {  
419.                   for (j = 0; j < top; j++)  
420.                   {  
421.                      
422.                        temp[mark][j] = stack[j];  
423.                   }  
424.                   for (a = 0; a+1 < top; a++)  
425.                   {  
426.                       sum[mark] =+ map.road[stack[a]][stack[a+1]]->length;  
427.                   }  
428.                   sum[mark] = sum[mark] + map.road[stack[a]][target]->length;  
429.  
430.                   if (mark != 0 && sum[mark] < sum[mark-1])  
431.                   {  
432.                        for (b = 0; b < top; b++)  
433.                        {  
434.                        mark = 0;  
435.                        temp[mark][b] = stack[b];  
436.                        }   
437.                   }  
438.                    mark++;  
439.                    top--;  
440.                    map.known[start] = false;  
441.                    break;  
442.               }  
443.            break;  
444.           }  
445.           if (!map.known[i])  
446.           {  
447.               DFS(map, stack, i, target, top, num, mark, sum, temp);  
448.           }  
449.        }  
450.        if (i == 13)  
451.        {  
452.            top--;  
453.            map.known[start] = false;  
454.        }  
455.    }  
456.}  
457.      
458.void shortestway(Graph map)  
459.{  
460.        int k, start;    
461.        string start_name;  
462.        int flag_1 = 0;  
463.        int tem[14][14];  
464.        //路径长度存在tem中  
465.        for (int i = 0; i < 14; i++)  
466.        {  
467.            for (int j = 0; j < 14; j++)  
468.            {  
469.                tem[i][j] = map.road[i][j]->length;  
470.            }  
471.        }  
472.        //弗洛伊德算法  
473.        for(k = 0; k < 14; k++)  
474.        {    
475.            for(int i = 0; i < 14; i++)  
476.            {    
477.                for(int j = 0; j < 14; j++)  
478.                {    
479.                    if(tem[i][k] < 666 && tem[k][j] < 666   
480.                        && tem[i][j] > tem[i][k] + tem[k][j])    
481.                        {  
482.                            tem[i][j] = tem[i][k] + tem[k][j];   
483.                        }         
484.                }    
485.            }    
486.        }    
487.          
488.        while (flag_1 == 0)  
489.        {   
490.            flag_1 = 1;  
491.            cout << "input start building:" ;  
492.            cin >> start_name;  
493.            start = translate(start_name, map, flag_1);  
494.  
495.            if (start != -1)  
496.            {  
497.              
498.        //按照路径长度进行排序  
499.                int exchange, vex[14], vexa;//存储序号变化  
500.                for (int i = 0; i < 14; i++)  
501.                {  
502.                    vex[i] = i;  
503.                }  
504.                for (int i = 0; i < 14; i++)  
505.                {  
506.                    for (int j = 0; j < 14; j++)  
507.                    {  
508.                        if (tem[start][j] > tem[start][j+1])  
509.                            {  
510.                            exchange = tem[start][j];  
511.                            vexa = vex[j];        //排序的同时还需要将对应序号交换
512.  
513.                            tem[start][j] = tem[start][j+1];  
514.                            vex[j] = vex[j+1];  
515.  
516.                            tem[start][j+1] = exchange;  
517.                            vex[j+1] = vexa;  
518.                            }  
519.                    }  
520.                }  
521.  
522.        //打印排序后的路径  
523.                for (int j = 0; j < 14; j++)  
524.                {  
525.                    while (vex[j] != start)  
526.                    {  
527.                    cout << map.building[start]->name << " to "   
528.                        << map.building[vex[j]]->name << ": "  
529.                        << tem[start][j] << endl;  
530.                    break;  
531.                    }  
532.                }  
533.            }  
534.            else {flag_1 = 0;}  
535.        }  
536.}  
