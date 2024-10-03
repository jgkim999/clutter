# Redis Example

## 

```bash
vcpkg install redis-plus-plus
vcpkg install fmt
vcpkg install spdlog
```

## Redis Cluster

Redis 는 CRC16(key name) mod 16384 로 분산함

4개의 노드를 만든다면

1번 노드 -> Slots 0 - 4095

2번 노드 -> Slots 4096 - 8191

3번 노드 -> Slots 8192 - 12287

4번 노드 -> Slots 12288 - 16383

4개의 노드를 실행하기 위한 docker-compse 파일

편의를 위해서 master-slave는 구성하지 않았음

[docker-compose.yml](./docker-compose.yml)

```bash
docker compose up -d
```

4개의 노드를 위한 설정 파일

[redis-node-1.conf](./redis-node-1.conf)

[redis-node-2.conf](./redis-node-2q.conf)

[redis-node-3.conf](./redis-node-3.conf)

[redis-node-4.conf](./redis-node-4.conf)

4개의 노드가 실행되면 1번 node에 접속해서 cluster를 생성한다.

```bash
docker exec -it redis-node-1 /bin/bash
```

redis-cli를 통해서 cluster를 생성한다.

```bash
redis-cli --cluster create redis-node-1:6379 redis-node-2:6379 redis-node-3:6379 redis-node-4:6379
>>> Performing hash slots allocation on 4 nodes...
Master[0] -> Slots 0 - 4095
Master[1] -> Slots 4096 - 8191
Master[2] -> Slots 8192 - 12287
Master[3] -> Slots 12288 - 16383
M: 7ecb02775c7824a5b827487a228ba7146d83b8ec redis-node-1:6379
   slots:[0-4095] (4096 slots) master
M: de982e7be56a9bb6c7a97568d429e384321dce7f redis-node-2:6379
   slots:[4096-8191] (4096 slots) master
M: 328e11960d5a90c08e419aed9763cc944f796bb3 redis-node-3:6379
   slots:[8192-12287] (4096 slots) master
M: 4cccafa3887eb22749aea3024685324b4064fc93 redis-node-4:6379
   slots:[12288-16383] (4096 slots) master
Can I set the above configuration? (type 'yes' to accept): yes
>>> Nodes configuration updated
>>> Assign a different config epoch to each node
>>> Sending CLUSTER MEET messages to join the cluster
Waiting for the cluster to join
.
>>> Performing Cluster Check (using node redis-node-1:6379)
M: 7ecb02775c7824a5b827487a228ba7146d83b8ec redis-node-1:6379
   slots:[0-4095] (4096 slots) master
M: 328e11960d5a90c08e419aed9763cc944f796bb3 172.20.0.4:6379
   slots:[8192-12287] (4096 slots) master
M: de982e7be56a9bb6c7a97568d429e384321dce7f 172.20.0.3:6379
   slots:[4096-8191] (4096 slots) master
M: 4cccafa3887eb22749aea3024685324b4064fc93 172.20.0.5:6379
   slots:[12288-16383] (4096 slots) master
[OK] All nodes agree about slots configuration.
>>> Check for open slots...
>>> Check slots coverage...
[OK] All 16384 slots covered.

```

redis-cli에서 CLUSTER INFO로 정보를 확인해 본다.

```bash
CLUSTER INFO

cluster_state:ok
cluster_slots_assigned:16384
cluster_slots_ok:16384
cluster_slots_pfail:0
cluster_slots_fail:0
cluster_known_nodes:4
cluster_size:4
cluster_current_epoch:4
cluster_my_epoch:1
cluster_stats_messages_ping_sent:52
cluster_stats_messages_pong_sent:56
cluster_stats_messages_sent:108
cluster_stats_messages_ping_received:53
cluster_stats_messages_pong_received:52
cluster_stats_messages_meet_received:3
cluster_stats_messages_received:108
total_cluster_links_buffer_limit_exceeded:0
```
