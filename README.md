# doudizhu

这是一款中国传统的游戏-斗地主。 <br><br>
1. 服务器分三个层次：基础技术(Public)、架构层(Template)、应用层(Servers)，基于这三个层次在这上面能开发任何应用； <br><br>
2. 基础技是会聚编程的技术精华，后期我也会不断的追架进出更多更底层的技术，请时时关注Opera_2015，为基础更新区； <br><br>
3. 架构层是灵活多变的，在一个分布式服务器中，各服务器之间的关联、协同（协调和同步）都存于个基本款架中；   <br><br>
4. 应用层主要是实现三个要求(MVC模型要求)：数据模型区(Pakcet)、数据控制区(Handler) 、服务器模块(Module)；  <br><br>

  
<br>架构层(Template)：<br><br>
1. 服务品层分为：LoginServer、DBServer、LobbyServer、AgentServer、GameServer等五组服务器； <br><br>
2. 数据包模型：RankPacket(排行包)、RoomsPacket(场次包)、RoomsPacket(房间包)、UserPacket(用户数据)、TablePacket(桌面信息包)等； <br><br>
3. 控制器由 PacketHandler里来定义：主要包括Protocol(协议)和FromAgentToGame(处理函数类); <br><br>
4. a线.LoginServer+DBServer=为预登录服务器组； <br><br>
  b线.AgentServer(N)+LobbyServer+DBServer=为登陆认证和大厅数据加载服务器组； <br><br>
  c线.AgentServer+GameServer=为用户游戏区服务器组； <br><br>
  c线是游戏复本的分布式服务器组处理线，依赖于b线做硬件组扩张； <br><br>
  负载的分布情况主要是LobbyServer(统一数据的派发)、AgentServer（高并发连接处理）、GameServer（游戏逻辑处理）、DBServer（数据存储）; <br><br>

