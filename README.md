程式碼用一個主程式和四個副程式組成，主程式按照附檔Essentials-metaheuristic-algorithm.pdf 第26頁程式碼，副程式分別為Tweak、total_profit、addTabu、inTabu。Tweak利用rand()%n來隨機更改一物品的取物情形，並且如果總重量超過capacity則捨棄，藉此讓Tweak有微調的功能。total_profit用for迴圈將每一個物品的profit乘上取物情形，得到總價值。addTabu將欲存放到tabulist的一組字串透過變數tabucount索引到插入位置，tabucount%tabu_size確保總字串數不會超過tabulist長度。inTabu用flag和for迴圈一一檢查該組字串是否在tabulist中，如在tabulist中flag=1否則flag=0。

第一組input

![image](https://github.com/Ray-web2/tabu0-1/blob/main/%E7%AC%AC%E4%B8%80%E7%B5%84.png)

第二組input
![image](https://github.com/Ray-web2/tabu0-1/blob/main/%E7%AC%AC%E4%BA%8C%E7%B5%84.png)
第三組input
![image](https://github.com/Ray-web2/tabu0-1/blob/main/%E7%AC%AC%E4%B8%89%E7%B5%84.png)

