# Redis Example

- [Redis Example](#redis-example)
  - [Redis Clust 접속을 위한 cpp 예제](#redis-clust-접속을-위한-cpp-예제)
    - [vcpkg 설치](#vcpkg-설치)
    - [Library 빌드](#library-빌드)
  - [Redis Cluster](#redis-cluster)

## Redis Clust 접속을 위한 cpp 예제

아래 라이브러리를 사용한다.

| Library |  |
|---------|--|
| [fmt](https://github.com/fmtlib/fmt) | 문자열 포매팅 |
| [spdlog](https://github.com/gabime/spdlog) | 로그 기록 |
| [redis-plus-plus](https://github.com/sewenew/redis-plus-plus) | Redis |
| [hiredis](https://github.com/redis/hiredis) | [redis-plus-plus](https://github.com/sewenew/redis-plus-plus)가 내부적으로 사용한다. |

라이브러리는 [vcpkg](https://learn.microsoft.com/ko-kr/vcpkg/get_started/overview)를 이용해서 빌드한다.

### vcpkg 설치

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg;
.\bootstrap-vcpkg.bat
```

### Library 빌드

```bash
vcpkg install redis-plus-plus
vcpkg install fmt
vcpkg install spdlog
```

## Redis Cluster

Redis IP는 192.168.0.47 라고 가정

Master 4대, Slave 4대를 위한 docker 설정 파일

[docker-compose.yml](./docker-compose.yml)

```bash
docker compose up -d
```

redis-cli에서 CLUSTER INFO로 정보를 확인해 본다.

```bash
CLUSTER INFO

cluster_state:ok
cluster_slots_assigned:16384
cluster_slots_ok:16384
cluster_slots_pfail:0
cluster_slots_fail:0
cluster_known_nodes:8
cluster_size:4
cluster_current_epoch:8
cluster_my_epoch:1
cluster_stats_messages_ping_sent:198
cluster_stats_messages_pong_sent:205
cluster_stats_messages_sent:403
cluster_stats_messages_ping_received:198
cluster_stats_messages_pong_received:198
cluster_stats_messages_meet_received:7
cluster_stats_messages_received:403
total_cluster_links_buffer_limit_exceeded:0
```

```bash
CLUSTER NODES

5df5bd2588a5b220beb1cbe63dae857c35ed88c5 192.168.0.47:6379@16379 master - 0 1728114681000 1 connected 0-4095
b0f2a22f61add4284e644310009ff4676ab0aba7 192.168.0.47:6380@16380 master - 0 1728114681292 2 connected 4096-8191
ef7c4b7d462c7b93dddfcc4eddbdde8366eaa084 192.168.0.47:6381@16381 myself,master - 0 0 3 connected 8192-12287
efbe653817b3d5b3c894f3a2d90e34035903d895 192.168.0.47:6382@16382 master - 0 1728114679272 4 connected 12288-16383
62f440df701a734270374d0b372c7686521c9d51 192.168.0.47:6383@16383 slave efbe653817b3d5b3c894f3a2d90e34035903d895 0 1728114679000 4 connected
6fd97df93cf42e60dd6b75703b59bba3027719f3 192.168.0.47:6384@16384 slave 5df5bd2588a5b220beb1cbe63dae857c35ed88c5 0 1728114682302 1 connected
7e01890277b8f81972d757f92aff8fef7f8ba814 192.168.0.47:6385@16385 slave b0f2a22f61add4284e644310009ff4676ab0aba7 0 1728114680000 2 connected
8539ef3abdca38f511492396a29865ad4659bc97 192.168.0.47:6386@16386 slave ef7c4b7d462c7b93dddfcc4eddbdde8366eaa084 0 1728114681000 3 connected
```

Redis 는 CRC16(key name) mod 16384 로 분산한다.

4개의 노드를 만든다면 아래와 같이 slot이 할당된다.

| External IP | Docker IP | Port | BUS Port | 할당 Slot | M/S |
|-------------|-----------|------|----------|------|-----|
| 192.168.0.47 | 172.20.0.2 | 6379 -> 6379 | 16379 -> 16379 | 0 - 4095 | Master |
| 192.168.0.47 | 172.20.0.3 | 6380 -> 6379 | 16380 -> 16379 | 4096 - 8191 | Master |
| 192.168.0.47 | 172.20.0.4 | 6381 -> 6379 | 16381 -> 16379 | 8192 - 12287 | Master |
| 192.168.0.47 | 172.20.0.5 | 6382 -> 6379 | 16382 -> 16379 | 12288 - 16383 | Master |
| 192.168.0.47 | 172.20.0.6 | 6383 -> 6379 | 16383 -> 16379 | | Slave |
| 192.168.0.47 | 172.20.0.7 | 6384 -> 6379 | 16384 -> 16379 | | Slave |
| 192.168.0.47 | 172.20.0.8 | 6385 -> 6379 | 16385 -> 16379 | | Slave |
| 192.168.0.47 | 172.20.0.8 | 6386 -> 6379 | 16386 -> 16379 | | Slave |
