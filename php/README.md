# Php

- [Php](#php)
  - [Windows](#windows)
    - [Php install](#php-install)
    - [Nginx install](#nginx-install)
  - [php 시작](#php-시작)
  - [nginx 시작](#nginx-시작)
    - [nginx process 확인](#nginx-process-확인)
    - [nginx 종료](#nginx-종료)
    - [nginx 재시작](#nginx-재시작)

## Windows

### Php install

https://windows.php.net/download#php-8.3

php.ini-production / php.ini-development

```bash
extention_dir = "php 설치 디렉토리 c:/php-8.3.10/ext"
date.timezone = Asia/Seoul
```

php.ini-development -> php.ini 로 복사

### Nginx install

https://nginx.org/en/download.html

nginx.conf 파일 수정

```bash
location ~ \.php$ {
    root           html;
    fastcgi_pass   127.0.0.1:9000;
    fastcgi_index  index.php;
    fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
    include        fastcgi_params;
}
```

## php 시작

```bash
start php-cgi.exe -b 127.0.0.1:9000
```

## nginx 시작

nginx 설치 폴더의 /hmtl 아래에 p_info.php 파일 생성

p_info.php

```php
<?php
    phpinfo();
?>
```

```bash
start nginx
```

http://localhost/p_info.php 를 접속해 본다.

php정보가 제대로 나오면 성공

### nginx process 확인

```bash
tasklist /fi "imagename eq nginx.exe"
```

### nginx 종료

```bash
nginx -s quit
```

### nginx 재시작

```bash
nginx -s reload
```
