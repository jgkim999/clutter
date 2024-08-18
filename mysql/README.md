# MySql

- [MySql](#mysql)
  - [general\_log 설정](#general_log-설정)

## general_log 설정

```bash
mysql -h localhost -P 3306 --protocol=tcp -u root -p

# general log 설정 확인
SHOW VARIABLES LIKE '%general%';
# general log 기록 위치 확인
SHOW VARIABLES LIKE '%log_output%';
# general_log 비활성화
set global general_log = OFF;
# general_log DB의 general_log TABLE에 log 기록
set global log_output = 'TABLE';
# general_log FILE로 기록
set global log_output = 'FILE';
# general_log가 TABLE과 FILE에 둘다 기록
set global log_output = 'TABLE,FILE';
# general_log 활성화
set global general_log = ON;
```
