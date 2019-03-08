
$(document).ready(function () {
	var availableTags = ['安庆西', '乳山', '文地', '东京城', '醴陵东', '光明城', '都江堰', '太阳沟', '钟家村', '合浦', '杨村', '洋县西', '彬县', '查干特格', '五通', '佛山', '下仓', '柳树屯', '鸭园', '鹰潭', '龙华', '二岔', '芨岭', '北海', '昭山', '孔滩', '蔡家沟', '商城', '新余', '任家店', '石林', '永济', '黑井', '绵阳', '平山', '东庄', '广安南', '长子', '东田良', '旬阳', '廊坊北', '冷水江东', '宣化', '哈密', '兴业', '汕头', '宣城', '洛阳', '金宝屯', '昂昂溪', '五常', '靖边', '兰考', '南岔', '乌兰哈达', '北京', '库尔勒', '沈阳南', '新乡', '换新天', '河口北', '前山', '离堆公园', '仙人桥', '沂水', '蚌埠南', '敖头', '连山关', '周家屯', '小金口', '魏杖子', '大红旗', '武隆', '古田北', '明港东', '二连', '泰安', '青岛北', '内江', '红寺堡', '杨漩', '宁波', '鹰手营子', '小西庄', '新华', '平遥古城', '陈官营', '西乡', '九三', '成都', '彭阳', '子长', '涪陵北', '李市镇', '邓家湾', '南江', '奉化', '宁国', '荣成', '石岭', '联合乡', '龙骨甸', '南观村', '青龙', '轵城', '清河门', '三阳川', '宝林', '茨坝', '于都', '南陈铺', '上海', '剑门关', '晋城', '汤山城', '巴彦郭勒', '东沟门', '土地堂东', '商河', '猴山', '怀柔北', '黄羊滩', '吉首', '峰高铺', '开化', '呼和浩特东', '共青城', '即墨北', '普洱渡', '乌伊岭', '庐山', '大余', '达拉特西', '库都尔', '通化', '榆树屯', '长征', '曹县', '营北', '左家', '达拉滨', '扶绥', '拉萨', '苏尼特左旗', '密云北', '平坝南', '荷塘', '长垣', '长农', '孙家', '龙里北', '济南西', '宜城', '武乡', '双鸭山', '灌水', '闹海营', '阿城', '羊尾哨', '随州', '浮图峪', '甘草店', '常平东', '金州', '卓资东', '大西', '和硕', '海宁', '当阳', '苏州新区', '钟山西', '西斗铺', '公主岭', '武威', '大营', '太原南', '怀化南', '柏村', '蒙自', '尼勒克', '八仙筒', '峻德', '金华南', '茶条沟', '邯郸', '前苇塘', '宝鸡南', '青铜峡', '浠水', '三源浦', '伊通', '大陆号', '天柱山', '西街口', '谢家镇', '东莞', '松岭', '庐江', '云居寺', '松树镇', '园墩', '三营', '忻州', '五大连池', '张桥', '邳州', '渠旧', '长寿北', '凤凰城', '姚千户屯', '水富', '歙县', '常平', '衡水北', '洋河', '北井子', '台州', '天桥', '杏树屯', '平原堡', '丰水村', '酒泉', '齐齐哈尔', '蚌埠', '大理', '宁东', '滨海', '莆田', '瓦房', '江源', '白沙坡', '新余北', '打柴沟', '青山', '东乡', '新晃', '太姥山', '新津', '陇县', '合阳北', '海宁西', '全椒', '抚远', '龙池', '哈业胡同', '乌鲁木齐', '西索木', '信阳', '小榆树', '西岗子', '龙山镇', '燕岗', '广南县', '盐池', '余粮堡', '绍兴东', '四合', '桥湾', '石家庄', '俞冲', '安口窑', '孤山', '黄羊湾', '暖泉', '莎车', '营口', '南头', '铁岭西', '二营', '杨木', '东城南', '新固镇', '渭南北', '新青', '霍城', '燕家庄', '一面山', '双龙山', '百宜', '富源', '沥林北', '涉县', '将乐', '三堂集', '阿金', '升昌', '悬钟', '水家湖', '麻山', '古家沱', '尼波', '桐城', '牙克石', '泡子', '武清', '北票南', '叶城', '三十家', '龙洞堡', '清水北', '新安', '张掖西', '黄花筒', '小岭', '山丹', '乌兰花', '宣汉', '十渡', '西柳', '哈力图', '万源', '绥中', '左岭', '孔家沟', '攀枝花', '平原东', '沈丘', '平湖', '碧州', '亚河', '庙庄', '龙川', '塔尔气', '烟台', '哈克', '乌龙泉南', '聂河', '如东', '鼎湖山', '双吉', '江都', '小新街', '良各庄', '克东', '长沙西', '砀山', '武陟', '河唇', '费县', '朝阳川', '凯里南', '高村', '南部', '分宜', '毛坝', '宁陵县', '图们北', '丹徒', '克一河', '苏集', '莲东', '广南卫', '化州', '平洋', '大足南', '保定东', '大徐屯', '花湖', '天桥岭', '晏城', '东戴河', '铁力', '招柏', '开封北', '古浪', '元龙', '昌图', '大磴沟', '纸坊东', '阿木尔', '碱柜', '徐州', '午汲', '二龙山屯', '霍林郭勒', '潘家店', '襄河', '佟家', '绿博园', '紫荆关', '柴河', '永川东', '王庄', '尼日', '盘关', '磁山', '东营子', '代湾', '巴东', '沙海', '来宾北', '忙罕屯', '株洲西', '铁厂', '白沙沱', '岱岳', '琼海', '平等', '新和', '柳毛沟', '苏州', '索伦', '温根托海', '大孤山', '孙吴', '桃山', '松河', '带岭', '万发屯', '兰岭', '高邑', '葫芦岛北', '晋中', '瓦屋山', '大兴沟', '莲江口', '凯北', '莒南', '公营子', '陶思浩', '张掖', '呼和浩特', '潮汕', '平凉南', '临邑', '哈尔滨北', '邵家堂', '武夷山北', '绿化', '和什托洛盖', '潞城', '王团庄', '永安乡', '水泉', '丰城南', '鹤庆', '黄陵南', '包头北', '花桥', '朔州', '二道桥', '无锡东', '鄠邑', '枣庄西', '文昌', '钟祥', '蛟河西', '大平房', '景泰', '明水河', '南河川', '灵丘', '武昌', '景德镇北', '保康', '五林', '汾河', '敖来', '湘潭北', '重庆', '昆山', '云彩岭', '梁山', '葛根庙', '望江', '平罗', '获嘉', '艾河', '合川', '河边', '鸡西', '庙宫', '李家坪', '汤池', '孟家岗', '朝阳南', '刀尔登', '桦南', '合肥北城', '怀仁东', '云霄', '利津南', '汝箕沟', '金华', '大连', '怀化', '杨树岭', '资阳北', '葵潭', '东淤地', '周口', '延吉西', '成吉思汗', '溆浦', '大板', '息烽', '麻柳', '土们岭', '新绰源', '王家营西', '罗平', '口前', '永胜', '卡伦', '迎祥街', '齐齐哈尔南', '古城镇', '东明县', '临江溪', '白奎堡', '海阳', '普定', '昆都仑召', '拉鲊', '天津南', '涡阳', '三门峡', '乌尔旗汗', '李旺', '溧水', '宾阳', '南靖', '东莞东', '三门县', '神头', '济南东', '绣峰', '青堆', '安庆沟', '贵阳北', '梁底下', '郫县', '塘沽', '鹤壁东', '东明村', '阳新', '大石寨', '龙岩', '正定', '贵溪', '灵石', '甸心', '舒兰', '丰泽公园', '榆树', '新窝铺', '北戴河', '喜德', '寿阳', '新立镇', '毛陈', '霍州东', '邓州', '吉舒', '本溪', '韶山南', '渭南镇', '冠豸山', '乃林', '大连北', '伊敏', '郑州', '五台山', '呼鲁斯太', '五女山', '平安', '龙游', '清远', '南召', '博鳌', '嘉峪关', '闻喜西', '后湖', '杨林', '平河口', '日照', '张家界', '风水沟', '高邑西', '黄瓜园', '博兴', '岢岚', '长虹', '民权', '江所田', '秦家庄', '乐昌', '查布嘎', '秦安', '康金井', '陶家屯', '巴日图', '豆罗', '图强', '石头', '虎尔虎拉', '大冶北', '祁家堡', '万州北', '烟筒屯', '盘州', '满洲里', '惠东', '大朗镇', '前进镇', '扶余', '张三营', '轩岗', '东通化', '焉耆', '桃村北', '超梁沟', '元谋', '查干湖', '仙林', '镇城底', '大庆东', '六盘水', '柳河', '陵城', '大口钦', '关村坝', '白石岩', '阳邑', '哈尔巴岭', '东安东', '嘉善', '松青', '范家屯', '黑河', '古镇', '豆沙关', '哲里木', '郭尔奔敖包', '新彦', '贺州', '葫芦岛', '杏树', '燕郊', '姚家', '喀什', '岷县', '芦家村', '滩头', '邢台东', '光明', '崖州', '大石桥', '哈达阳', '秦家', '大屯', '四家子', '扎音河', '三家寨', '阿克苏', '范镇', '洛碛', '陈相屯', '库伦', '富源北', '青县', '无为', '轮台', '本溪新城', '抚州东', '新津南', '永州', '新寒岭', '鄄城', '兰考南', '阜宁', '长武', '下社', '固原', '普兰店', '巴山', '南昌', '伊图里河', '凉红', '紫阳', '小白', '保家楼', '哈尔滨', '昌平北', '狼尾山', '红砂坝', '兑镇', '铜陵北', '兰州西', '坪石', '阳岔', '高台', '红砂岘', '吕梁', '双辽', '大安', '大杨树', '井冈山', '防城港北', '戚墅堰', '亳州', '能家', '德兴东', '弯坵', '尤溪', '山市', '建三江', '通辽', '金银潭', '豆庄', '原平', '萍乡北', '金昌', '柳树', '尚志', '蓬莱市', '定南', '五棵树', '六安', '茅草坪', '天祝', '盘锦', '亭亮', '大虎山', '介休东', '永修', '盐津', '颍上', '洞井', '昌乐', '凭祥', '谷城', '曾家坪子', '江油北', '潼南', '四合永', '大英东', '九龙', '官高', '八虎力', '大苴', '白石山', '黄松甸', '安庆', '西安南', '曹子里', '六道河子', '水源', '天门', '天岗', '长寿湖', '普者黑', '晋州', '三花石', '芦沟', '无锡新区', '阳高', '昆山南', '龙丰', '冯屯', '旬阳北', '宁海', '前窑', '宽甸', '花山南', '江宁', '蕲春', '宜耐', '辽阳', '平南南', '大战场', '白沟', '红安西', '兴隆店', '凤县', '高桥镇', '博白', '苏州北', '月山', '月亮田', '什里店', '布海', '老城镇', '洛阳东', '敦化', '鹤北', '云梦', '春亭阁', '石湖', '余江', '大杖子', '古城子', '中卫', '太平镇', '吉安', '金山屯', '沁河北', '德令哈', '同心', '岳阳东', '棋子湾', '王安镇', '乐善村', '林西', '河津', '阳泉', '灵武', '兴隆镇', '草海', '溧阳', '达州', '汕尾', '兖州', '赣州', '新民', '白银西', '白沙', '猛洞河', '敬梓场', '渑池南', '磨刀石', '石桥子', '完工', '发耳', '蒲城东', '涟源', '榆次', '赵庄', '沙坪坝', '黄梅', '公主岭南', '武功', '大关', '南城司', '德伯斯', '天津', '清原', '内江南', '盐城', '梁平南', '安阳', '九江', '阎良', '中兴', '寒葱沟', '香樟路', '观沙岭', '东边井', '桃村', '南丰', '二井', '双丰', '道劳杜', '金刚沱', '艾家村', '高谷', '徐水', '唐河', '苇河', '清涧县', '雅河', '湛江', '银镇', '濮阳', '伊敏索木', '襄汾', '玉山', '丹阳北', '德昌', '乌兰', '安化', '朝中', '漳县', '四分滩', '恒地营', '晋江', '常州', '杭州', '嘎什甸子', '毛坝关', '瓦房店西', '沙沙坡', '迎春', '富宁', '丹凤', '吴家屯', '台安', '郫县西', '濑湍', '靖州', '七苏木', '瓦房店', '临城', '三义井', '沙湾', '干溪沟', '虎山', '广州', '永寿', '登沙河', '项城', '汉寿', '太平川', '开安', '官厅', '高家村', '安图西', '唐山南', '宁强南', '西昌', '月华', '碾子山', '褚家湾', '阳信', '磐石', '临海', '黄家店', '哈拉海', '吐哈', '祥云', '双城堡', '姜堰', '郴州西', '上仓', '枫林', '峨眉山', '大方南', '菇园', '圣浪', '拉林', '东光', '东升', '福清', '祁县东', '佛岭', '池州', '营城', '中宁', '曲家店', '霍尔果斯', '明城', '鄂尔多斯', '白水镇', '海东西', '广州南', '友好', '拉白', '牧原', '从江', '慈利', '翠峰', '双阳', '图里河', '秧草地', '军粮城北', '道清', '湘潭', '红峰', '林海', '介休', '东来', '腰栈', '雨格', '大湾子', '长河碥', '建水', '滕州东', '长治', '金月湾', '中宁南', '刘家店', '定襄', '兴宁', '弥勒', '梧州南', '红兴隆', '秦皇岛', '白河', '十堰', '酒泉南', '哈尔滨东', '厦门北', '藁城', '三穗', '北京西', '赤壁北', '咸宁北', '绥芬河', '惠州', '贲红', '上板城', '乌兰浩特', '阿寨', '白山市', '娄山关南', '美溪', '长城', '石泉县', '福田', '南宁', '农安', '长沙南', '银川', '常德', '汤阴', '扶余北', '千阳', '衡水', '小池口', '上海南', '五龙背', '化德', '翠岗', '韶关', '新安庄', '铁口', '赤峰东', '禄丰南', '石城', '辛集', '平峪', '贵定县', '南江口', '彭州', '汤逊湖', '太和北', '玉林', '南山北', '官厅西', '济南', '甘谷', '两当', '长发屯', '三把火', '富裕', '滦平', '达家沟', '汉口', '都匀东', '正镶白旗', '万宁', '埃岱', '石门村', '苏家屯', '黄柏', '济宁', '华山北', '龙嘉', '大荔北', '侯马', '哈达铺', '楚鲁图', '李家', '遵义', '嘉善南', '静海', '东大坝', '福州南', '临河', '临沂', '阳朔', '芙蓉南', '三家店', '大灰厂', '门源', '黄州', '下花园', '铜仁南', '六盘山', '温泉寺', '乐平市', '罗山', '黄村', '开阳', '五家', '沁阳', '海阳北', '青城山', '新都东', '东胜西', '汾阳', '平邑', '重庆北', '平凉', '张百湾', '金口河', '萍乡', '堡子湾', '南雄', '永郎', '孟津', '柳毛', '平型关', '师庄', '共和', '五道河', '鲅鱼圈', '图们', '通安驿', '章丘', '章党', '三江口', '广汉北', '富锦', '小南海', '六枝', '吉新河', '公庙子', '丹东西', '神池', '繁昌西', '新会', '八面通', '赤峰西', '万乐', '新郑机场', '热水', '黎塘', '正定机场', '沙城', '广德号', '新沂', '临汾西', '德惠西', '永济北', '深井子', '通远堡西', '宋', '中嘴', '源迁', '胶州', '白音察干', '瓦祖', '修武西', '长坡岭', '平台', '油溪', '前锋', '四平', '阳平关', '哈达', '晨明', '郑州东', '西里', '红岘台', '广宁', '隆昌北', '白城', '十家子', '青田', '桥北', '沃皮', '成都南', '楚山', '新晃西', '咸阳秦都', '闽清北', '庙山', '樟木头东', '漳州', '甘旗卡', '安广', '定西', '富拉尔基', '海城西', '中寨', '日喀则', '乌海北', '向阳', '江宁西', '艾不盖', '涿州东', '黑台', '兴凯', '桂林北', '黄流', '高台南', '西固城', '舍力虎', '神州', '岐山', '洛阳龙门', '莱西北', '姚安', '民族', '羊者窝', '南宁西', '福山口', '孝南', '上谷', '唐山', '牛家营子', '山海关', '汇流河', '泰山', '亚布力南', '南湾子', '朗乡', '五莲', '汉川', '杭锦旗', '荣昌北', '诸城', '刚察', '巴林', '应城', '黄冈东', '裕国', '塔崖驿', '曲阜', '霸州西', '低庄', '福安', '背荫河', '蓝村', '通州', '武义北', '高碑店', '牟平', '大官屯', '苏州园区', '定西北', '三水北', '李石寨', '鳌江', '木头营子', '桑根达来', '板塘', '高碑店东', '天河街', '海口', '柏林', '加格达奇', '景德镇', '锦州', '保定', '温州南', '下城子', '三门峡南', '镇安', '黑冲滩', '元宝山', '四方台', '白泉', '大足', '黄冈西', '淮北北', '新高峰', '汪清', '扎赉诺尔西', '铁岭', '自贡', '洪洞西', '邢台', '孝感东', '格尔木', '桃园', '燕子砭', '西平西', '武汉', '新友谊', '沁县', '白芨沟', '上腰墩', '古冶', '九台南', '松桃', '三十里堡', '石磷', '满归', '成都东', '五府山', '照福铺', '沭阳', '密山西', '辽源', '饮马峡', '涵江', '沟帮子', '汉中', '临江场', '遂宁', '东台', '红江', '平果', '咸宁南', '英德', '淮滨', '鱼泉', '铜陵', '郭家屯', '荣昌', '泉阳', '双城北', '连云港东', '头道桥', '长山屯', '马龙', '白音胡硕', '黄土店', '上高镇', '樟树东', '湾沟', '柳林南', '狮山', '山阴', '施家嘴', '井南', '德安', '扎鲁特', '阿里河', '西湖东', '贵定北', '五原', '麻阳', '土溪', '后寨', '柯柯', '酉阳', '九营', '丽江', '伊春', '茂名', '南朗', '冕山', '宜兴', '烟台南', '丹霞山', '临澧', '敖汉', '榆树川', '沙桥', '张辛', '滁州', '瑞金', '下台子', '美兰', '丰广', '辽中', '肃宁', '山河屯', '南洼', '小山', '羊木', '庆安', '天河机场', '宜宾南', '青白江东', '彭山北', '苍坪', '瓦拉干', '墨玉', '利川', '石林南', '大田边', '新邱', '民乐', '胜芳', '太平庄', '白合', '巢湖东', '旌德', '泽普', '绅坊', '华家', '松江南', '泊头', '石人', '小宋', '沙河市', '永登', '广州东', '乐武', '苍溪', '武山', '汝州', '两家', '老岭', '进贤南', '绩溪北', '永康南', '鹤岗', '辛集南', '南陵', '榆中', '鹿道', '上饶', '孝西', '淮北', '仙游', '南宁东', '贵阳东', '露水河', '长春', '台前', '德清西', '天津北', '松原', '南通', '闻喜', '沙园', '城固', '吉林', '信宜', '万年', '鸳鸯镇', '芜湖', '蓬安', '绥德', '秀山', '横峰', '大庆', '到保', '怀集', '端州', '磐安镇', '松树台', '义乌', '北岗', '白洋淀', '昆阳', '郑州西', '平昌', '北马圈子', '美岱召', '宁东南', '岳池', '庄河北', '建瓯西', '莱阳', '徐州东', '大涧', '牛家', '景州', '梅江', '斗沟子', '白马井', '干塘', '安塘', '永川', '鹤立', '阿巴嘎旗', '茂名西', '阿尔山北', '岩会', '城子坦', '明光', '岳阳', '准格尔', '通州西', '东方红', '乌奴耳', '汨罗东', '汤头沟', '惠州南', '乐跃', '黄泥崴子', '英吉沙', '绕阳河', '伊宁东', '江山', '恭城', '渭源', '桦林', '大盘石', '亭林', '南芬北', '治安', '许家台', '高平', '串子沟', '人民医院', '武当山', '昆明', '西大庙', '湖州', '老爷岭', '新化南', '昌黎', '丰镇', '黄山', '车转湾', '兴泉堡', '迤资', '平庄南', '皋兰', '泰康', '五十家子', '马盖图', '阳泉曲', '佳木斯', '北屯市', '根河', '荆门', '源潭', '团结', '一面坡', '通渭', '衡阳', '唐家湾', '乌兰胡同', '舒城', '南杂木', '滕州', '温岭', '影壁山', '树木岭', '桐柏', '大民屯', '阳泉北', '枣子林', '湘府路', '容桂', '对青山', '新李', '纪家沟', '衡山', '归流河', '海拉尔', '白涛', '淄博', '代县', '资中', '上普雄', '齐哈日格图', '余姚北', '古交', '三亚', '山湾子', '樟木头', '榆林', '临清', '南芬', '长甸', '磁窑', '柏果', '甘洛', '赛汗塔拉', '灵石东', '果松', '沂南', '青岛', '坡底下', '大石头', '大荔', '塔河', '郓城', '内江北', '盘锦北', '复盛', '潮州', '葛店南', '吴官田', '曲靖', '婺源', '江密峰', '塔源', '隆化', '土贵乌拉', '漯河西', '瓜州', '彭水', '兴莲', '武胜', '白狼', '白涧', '熊岳城', '德清', '交城', '锡林呼都嘎', '古城', '姜家', '西阳村', '鹿寨', '暮云', '灵璧', '阿克陶', '陇南', '下马塘', '界首市', '玉泉', '抚宁', '横江', '黄冈', '春阳', '宝龙山', '运城', '汤原', '江桥', '耒阳西', '盘古', '龙口市', '马莲河', '兰州', '华城', '西武匠', '东港北', '沈阳北', '金林', '南充北', '霸州', '柴沟堡', '霍邱', '白水江', '泔溪', '西岭口', '九郎山', '高山子', '郁南', '凤州', '向阳川', '经棚', '向塘', '溆浦南', '凌海', '桥头', '安顺', '梅州', '广元', '阳明堡', '上板城南', '深圳北', '马兰', '边沟', '陆丰', '潍坊', '奎屯', '仙桃西', '惠山', '锡林浩特', '威海', '霍州', '太原', '一步滩', '奇峰塔', '稷山', '永城北', '开原西', '贵阳', '安康', '子洲', '闵集', '榕江', '察尔汗', '桐梓北', '滦河沿', '长沙', '海口东', '建宁县北', '重庆西', '曹家营子', '岭南', '天镇', '漳浦', '新县', '石河子', '镇西', '奎山', '十八台', '牡丹江', '太谷西', '南阳寨', '碧江', '句容西', '鄂州东', '长冲', '鲁山', '潢川', '信阳东', '歙县北', '石人城', '应县', '宣威', '亚复', '金山园区', '坪上', '陶赖昭', '合肥', '宣家沟', '兴平', '玉石', '公积坂', '杜拉尔', '赫尔洪得', '坝梁', '深圳东', '清徐', '忠工屯', '株洲南', '绍兴北', '莱西', '王场', '阿尔山', '四会', '龙塘坝', '福州', '古田会址', '北滘', '高州', '宏庆', '阿拉山口', '安平', '三都县', '巴彦高勒', '乌拉特前旗', '嘉峪关南', '茂林', '修文县', '常州北', '水地', '大旺', '兴城', '宝鸡', '孤山子', '安顺西', '长治北', '兴安岭', '嘉兴南', '帽儿山', '上海西', '寒岭', '三道营', '平遥', '藤县', '三河县', '朝天南', '肇庆东', '北板桥', '珠海北', '陵水', '渭南', '苏雄', '泉州', '饶阳', '白银哈尔', '灵山', '咸阳', '朱家沟', '阳谷', '东镇', '集安', '侯马西', '塔尔根', '海安县', '奈曼', '平度', '卫星', '耒阳', '伊宁', '孝感北', '南平北', '驼腰岭', '武穴', '神木', '全州南', '加南', '玉门', '当涂东', '祁东', '乌海西', '云东海', '福利屯', '清水', '威宁', '洮南', '通天屯', '盖州', '汉阴', '平社', '德保', '苔青', '天义', '宜宾', '虢镇', '广安', '西昌南', '朝阳地', '武威南', '王岗', '核桃园', '嵯岗', '笔架山', '庙阳', '铜仁', '平旺', '商都', '板石河', '察素齐', '开福寺', '双流西', '韩城', '宿州东', '密山', '革居', '铜罐驿', '临泽南', '聊城', '鹰潭北', '拉哈', '凤城东', '白壁关', '揭阳', '富海', '北屯', '新乡东', '新化', '定陶', '西阳岔', '营盘水', '清水县', '泗阳', '东营南', '北安', '依安', '扎兰屯', '小儿坪', '道滘', '五叉沟', '新江', '塘豹', '甘河', '红果', '绩溪县', '沈家', '福临堡', '陆良', '沙坡头', '南口前', '新杖子', '庙城', '徘徊北', '泾川', '哈尔滨西', '小月旧', '桃映', '延吉', '田家沟', '大雅河', '大兴', '黄泥河', '盖州西', '普安', '小河沿', '流水沟', '阳春', '六道河', '西六方', '亚龙湾', '曲江', '德惠', '桓龙湖', '夏拉哈马', '石柱县', '大东', '长寿', '沙马拉达', '宝拉格', '古源', '乾县', '丰城', '德州', '金沟屯', '天水', '霞浦', '青沟子', '萨拉齐', '东营', '车墩', '横沟桥东', '讷河', '禹城东', '无锡', '捏掌', '宜春', '留庄', '米易', '半截河', '运城北', '红星', '神树', '华容东', '兰州东', '孔垄', '七甸', '龙泉寺', '当雄', '枝江北', '鞍山西', '青川', '泗县', '桂林西', '柞水', '商南', '林子头', '卫辉', '平顶山西', '高密', '麻城北', '青州市', '宝华山', '老府', '镇赉', '贺胜桥东', '扬州', '乐都南', '太原东', '东江新村', '田梁子', '咸宁东', '蒙自北', '进贤', '包头西', '青莲', '泉江', '同江', '彝良南', '小东', '东元庆', '滦河', '榆树沟', '莒县', '连江', '白音他拉', '镇江南', '桂林', '眉山东', '富县东', '姚渡', '疏勒河', '华容南', '羊臼河', '明珠', '宿松', '新桥', '淮南', '榆社', '驻马店西', '怀柔', '尖峰', '资阳', '玉田县', '徐家', '文登东', '石脑', '免渡河', '赶水东', '乐山', '东丰', '弋阳', '石门子', '营山', '大林', '商丘南', '申家店', '鄱阳', '扎赉诺尔', '辉河', '江津', '大通西', '普雄', '钦州东', '巨野', '包头东', '巴楚', '锦河', '漯河', '茂舍祖', '马林', '沐滂', '丰顺', '冕宁', '安陆', '黑旺', '广宁寺', '临汾', '沈阳', '乌兰察布', '厦门', '窑上', '黑水', '开鲁', '韦庄', '东湾', '古东', '铁佛寺', '林盛堡', '永福南', '瓦窑坝', '青水山', '渠县', '大武口', '息县', '开封', '南昌西', '镜铁山', '沙岭子西', '铁西', '吐鲁番北', '花棚子', '北磴', '苍石', '黄石北', '大坝', '七台河', '阳澄湖', '汉源', '衡山西', '平关', '德兴', '长临河', '昭通北', '北京东', '田阳', '王府', '盐津北', '滦县', '三间房', '庙岭', '凌源', '凤凰机场', '永甸', '普安县', '大口屯', '江门东', '福鼎', '武夷山东', '五道沟', '余杭', '博克图', '金城江', '中川机场', '松树林', '双凤驿', '民和南', '河洛营', '鄯善北', '东方', '安靖', '峡江', '红山', '桐乡', '平庄', '襄阳东', '松江河', '南仇', '石家庄北', '许三湾', '板城', '乌鲁木齐南', '中和', '朝阳镇', '巴中', '始兴', '承德东', '双河镇', '嘉祥', '韩麻营', '八方山', '连珠山', '雁荡山', '大营镇', '石家庄东', '一间堡', '永和', '菏泽', '泗水', '磁县', '枣阳', '哈尔盖', '高各庄', '兰岗', '西宁', '沙湾县', '博乐', '赵光', '阿图什', '蔺家楼', '五龙背东', '乌鲁布铁', '五寨', '常平南', '龙江', '诏安', '祁阳', '湟源', '石嘴山', '海晏', '司家岭', '孙镇', '岔河', '合肥南', '泰州', '低窝铺', '绥阳', '吉文', '鸽子洞', '火炬沟', '鹿寨北', '上海虹桥', '楚雄南', '宜昌东', '双峰北', '狮山北', '宜良北', '下普雄', '上万', '海城', '里木店', '义县', '安亭北', '温春', '南大庙', '白桦排', '下板城', '德日斯图', '明安', '浩良河', '普宁', '松树', '赤峰', '新林', '南桥', '三合庄', '黄羊镇', '阿勒泰', '朱家窑', '鄯善', '长春西', '大雁', '小寺沟', '泰宁', '福山镇', '杨杖子', '玛纳斯', '龙沟', '崔黄口', '崇左', '新天', '香兰', '郁山', '嘎什吐', '莲花山', '陆川', '银瓶', '安阳东', '柳园', '南京', '田东北', '靖西', '励家', '尔赛河', '阜阳', '库车', '株洲', '京山', '宝坻', '潮阳', '阿龙山', '白银市', '燕山', '乌海', '罕达盖', '乐东', '彝良', '四马架', '唐山北', '福生庄', '庆盛', '大庆西', '喀喇其', '土门子', '鄂州', '苏北', '西安北', '刘沟', '祁县', '吐鲁番', '三关口', '黄陵', '简阳南', '龙南', '新松浦', '长庆桥', '八苏木', '宁安', '中山北', '怀仁', '轸溪', '玉山南', '澧县', '金山卫', '弥渡', '关岭', '皮山', '小扬气', '东二道河', '遂溪', '泰来', '甲山', '通道', '老莱', '贵港', '昆明南', '小榄', '海林', '延安', '安达', '井陉', '焦作', '兴和西', '德阳', '宁乡', '三原', '野三坡', '小河镇', '裴德', '惠环', '通远堡', '安德', '绥棱', '纳雍', '谷山', '玉溪', '垫江', '香坊', '银滩', '桐梓东', '额济纳', '永乐店', '礼泉', '英德西', '曲阜东', '穆棱', '东南营子', '门达', '略阳', '克山', '烟台西', '沙沱', '槐荫', '煤田', '古莲', '北京南', '商丘', '南湖东', '莱芜东', '黄山北', '小得江', '益阳', '兰家屯', '民权北', '如皋', '草河口', '辰清', '廉江', '米沙子', '砚川', '顺德', '岭北', '亚布力', '洛门', '杭州东', '鹤山', '定州东', '信丰', '会昌北', '璧山', '缙云西', '长兴南', '东富', '南博山', '潜江', '金山北', '晋城北', '甘泉北', '平房', '肇庆', '林口', '普湾', '来宾', '四平东', '营街', '朱日和', '安图', '鸡东', '五营', '米脂', '锦州南', '烟筒山', '风陵渡', '花园口', '锦和', '三江南', '建昌', '黔江', '蒲城', '辰溪', '山城镇', '张家川', '德仁', '会同', '文水', '肇东', '营口东', '阳曲', '阿乌尼', '天水南', '双流机场', '师宗', '倭肯', '济源', '西麻山', '开通', '威海北', '歪头山', '贺家店', '尹地', '南京南', '小市', '松江', '邹城', '泰和', '开原', '巢湖', '曲水县', '砬子河', '常庄', '阆中', '洞庙河', '广州北', '滴道', '新凉', '嵩明', '偏岭', '拉古', '广通北', '大辛庄', '八面城', '商洛', '韩府湾', '汐子', '蔡家坡', '深圳西', '大丰', '瑞昌西', '白旗', '阜新南', '呼兰', '宁明', '西林', '二道沟门', '白鸡坡', '资中北', '和田', '东海', '东坡', '韶关东', '高安', '蛟河', '衡阳东', '涞源', '平泉', '女儿河', '萧县北', '岩山', '山坡东', '惠农', '平田', '青神', '大乌苏', '石林西', '新干', '宁德', '枣庄东', '建始', '百色', '黄\ue244', '深州', '云山', '苍南', '氡泉', '文登', '乐清', '杨陵南', '黄河景区', '千河', '寮步', '诸暨', '巩义南', '安多', '临泽', '花家庄', '隆安东', '老边', '犀浦', '芦台', '丹阳', '互助', '朝阳村', '集宁南', '四道湾', '西小召', '枣庄', '西丰', '瑞安', '洪河', '石门县北', '鹤壁', '蓟州', '东海县', '洛湾三江', '靖远', '通北', '临江', '南城', '中山', '凌源东', '成高子', '兴国', '芦家庄', '惠安', '周家', '威岭', '襄汾西', '庄桥', '乌固诺尔', '林东', '重庆南', '沧州西', '营盘湾', '红花沟', '南尔岗', '克拉玛依', '陇西', '南翔北', '新坪田', '麻城', '白果', '白彦花', '七营', '深圳', '绥中北', '三明北', '威舍', '双子河', '藁城南', '叶榭', '杨树湾', '沈家河', '德州东', '临高南', '黎城', '新立屯', '云浮东', '白河县', '杨柳青', '班猫箐', '枣林', '清河城', '老营', '隆昌', '饶平', '大同', '灯塔', '通化县', '珲春', '娘子关', '彰武', '杨家店', '赛乌苏', '蒲坝', '统军庄', '襄阳', '塔哈', '佛山西', '南汤', '大杨树东', '吴桥', '锡铁山', '兰溪', '兰陵北', '乐昌东', '通海', '秦岭', '柳园南', '皮口', '江油', '汤旺河', '刘家河', '桂平', '威箐', '南峪', '湖口', '龙爪沟', '宝泉岭', '白沙铺', '金杖子', '岔江', '珠海', '西安', '鞍山', '大山铺', '三水南', '包头', '大扬气', '二龙', '新绛', '邵阳北', '沟口', '新阳镇', '马鞍山东', '松山湖北', '海伦', '丹东', '原林', '光山', '精河南', '靖远西', '双石桥', '灵宝西', '临西', '红光镇', '羊圈子', '崇信', '滁州北', '抚顺北', '红彦', '芷江', '柳家庄', '老羊壕', '铜鼓溪', '春申', '绥化', '洪洞', '柳州', '柳沟', '邯郸东', '扎罗木得', '定远', '定州', '朱杨溪', '百里峡', '永嘉', '九台', '棋盘', '东兴', '于家堡', '吴家川', '角美', '桐子林', '杨家营', '泽民', '福海', '丽水', '张台子', '海北', '恩施', '三家子', '廊坊', '遵义南', '讷尔克气', '那曲', '武安', '安家', '卓资山', '涿州', '屏边', '阿贵图', '敦煌', '土桥子', '宁武', '横道河子', '兴隆县', '旗下营', '虎门', '繁峙', '尖山', '永丰营', '任丘', '邵阳', '抚州', '中台子', '张兰', '漠河', '鲁番', '白云鄂博', '三汇镇', '峨边', '麓谷', '鼎湖东', '都昌', '龙镇', '枣强', '宋城路', '孤山口', '太谷', '石坝', '井店', '勃利', '固始', '嘉兴', '叶柏寿', '珞璜南', '越西', '顺德学院', '兴安北', '虎林', '长汀南', '小雨谷', '玉舍', '乌拉山', '天门南', '栟茶', '建安', '邵东', '大青沟', '伊拉哈', '高头', '杨岗', '安富镇', '佛坪', '罗江东', '镇江', '田心东', '沧州', '长汀镇', '深圳坪山', '嫩江', '涪陵', '金河', '昭通', '土牧尔台', '淮南东', '长兴', '仲恺', '宣和', '城固北', '桦皮厂', '娄底', '滨州', '姑家堡', '滨海北', '宿州', '永泰', '阿南庄', '河口南', '沙坨子', '先锋', '兰棱', '砀山南', '兰州新区', '桥西', '渡市', '白马', '顺义', '织金', '南充', '襄垣', '太湖', '长潭沟', '曲靖北', '荆州', '杨陵', '弋江', '勉县', '常山', '阿房宫', '绿潭', '大堡', '小关溪', '上园', '朝天', '水洞', '丰都', '太阳山', '马三家', '小村', '东辛庄', '定边', '泾县', '金寨', '夏官营', '劲松', '淮安', '鲘门', '都格', '高滩', '瓦窑田', '广顺场', '罗源', '广德', '河源', '草市', '承德', '梨树镇', '梅河口', '小哨', '北宅', '郴州', '上西铺', '迎宾路', '衢州', '宜州', '南阳', '昌图西', '三水', '綦江东', '天津西', '徽县', '小姑家', '樟树', '二道湾', '丰乐镇', '大竹园', '娄底南', '张维屯', '许昌东']
	try{
	$("#start_s").autocomplete({
		source: availableTags
	});
	$("#end_s").autocomplete({
		source: availableTags
	});
	}
	catch(e)
	{
		alert(e);
	}

	var glass_effect_kind = '';
	if ($(".topnav").attr("pagename") == "login") {
		$(".glass_effect").addClass("glass_effect2");
		$(".glass_effect2").removeClass("glass_effect");
		$("body").css("background-image", "url(/static/img/5.jpg)");
		glass_effect_kind = 2;
		$.post("/get_re", {}, function (data) {
			var num = data.length;
			for (var i = 0; i < num; ++i) {
				$("#tmp").html(ticket_html1.join(''));
				$("#tmp .search_result").attr("kind_tag", data[i].kind_tag);
				$("#tmp .train_id").html(data[i].kind);
				$("#tmp .train_id_2").html(data[i].name);
				$("#tmp .starting_station time").html(data[i].dep_time);
				$("#tmp .ending_station time").html(data[i].des_time);
				$("#tmp .starting_station .station_name").html(data[i].dep);
				$("#tmp .search_result").attr("date_tag", data[i].date);
				$("#tmp .search_result").attr("st_tag", data[i].dep);
				$("#tmp .search_result").attr("train_id_tag", data[i].train_id);
				$("#tmp .search_result").attr("ar_tag", data[i].des);
				var d1 = data[i].date.substr(0, 7);
				var d2 = data[i].date.substr(8, 2);
				$("#tmp .seat_contain_text .buy_text_1").html(d1);
				$("#tmp .seat_contain_text .buy_text_2").html(d2 + '日');
				if (data[i].dep == data[i].station[0])
					$("#tmp .starting_station .station_name").prepend('始 ');
				$("#tmp .ending_station .station_name").html(data[i].des);
				if (data[i].des == data[i].station[data[i].station.length - 1])
					$("#tmp .ending_station .station_name").append(' 终');
				if (get_minute(data[i].dep_time) > get_minute(data[i].des_time))
					$("#tmp .ending_station time").append('<span style="font-size: 13px; letter-spacing: -3px">+1</span>');
				var m = data[i].price.length;
				for (var j = 0; j < m; ++j)
					$("#tmp .seat_contain_list").append(ticket_html2.join(''));
				var $seats = $("#tmp .seat_contain_list").find(".seat_contain");
				for (var j = 0; j < m; ++j) {
					var $now = $($seats.get(j));
					$now.attr("rem_tag", data[i].remain[j]);
					$now.attr("name_tag", data[i].seat_name[j]);
					$now.find(".buy_text_1").html(data[i].seat_name[j]);
					if (data[i].remain[j] != -1) {
						if (data[i].remain[j] > 0)
							$now.find(".seat_contain_text").addClass("available");
						$now.find(".buy_text_2_2").html(data[i].remain[j] + '<span style="font-size: 12px">张</span>');
						$now.find(".buy_text_2_2").css("left", "0");
						$now.find(".buy_text_3").html('￥' + data[i].price[j]);
						$now.find(".buy_text_4").html('退订');
					}
					else
						$now.find(".buy_text_2_2").html('--');
				}
				m = data[i].station.length;
				$("#tmp .train_id_info_detail").append(data[i].name + ' | 全程' + get_time(data[i].arr_time[0], data[i].arr_time[m - 1]) + ' | 此程' + get_time(data[i].dep_time, data[i].des_time));
				$("#tmp .station_detail .starting_station").html(data[i].station[0] + '<br>' + data[i].arr_time[0]);
				$("#tmp .station_detail .ending_station").html(data[i].station[m - 1] + '<br>' + data[i].arr_time[m - 1]);
				if (get_minute(data[i].arr_time[0]) > get_minute(data[i].arr_time[m - 1]))
					$("#tmp .station_detail .ending_station").append('<span style="font-size: 13px;">+1</span>');
				for (var j = 0; j < m; ++j)
					$("#tmp .station_list").append(ticket_html3.join(''));
				var $station = $("#tmp .station_contain");
				for (var j = 0; j < m; ++j) {
					var $now = $($station.get(j));
					$now.find(".station_text_1").html(data[i].station[j]);
					$now.find(".station_text_2").prepend(data[i].arr_time[j]);
					$now.find(".station_text_3").html(data[i].stan_time[j]);
					if (get_minute(data[i].arr_time[j]) < get_minute(data[i].arr_time[0]))
						$now.find("span").html('+1');
				}
				$("#result").append($("#tmp .search_result"));
			}
			$(".glass_effect").addClass("glass_effect2");
			$(".glass_effect2").removeClass("glass_effect");
			$all = $(".search_result");
			$(".train_info").hide();
			tag_reset();
		});
	}

	$(".swap_button").click(function () {
		var tmp = $("#start_s").val();
		$("#start_s").val($("#end_s").val());
		$("#end_s").val(tmp);
	})

	$("#start_s").keyup(function () {
		if (getByteLen($("#start_s").val()) == 0)
			$("#in_city").show();
		else
			$("#in_city").hide();
	})
	$("#end_s").keyup(function () {
		if (getByteLen($("#end_s").val()) == 0)
			$("#in_city").show();
		else
			$("#in_city").hide();
	})

	jQuery.fn.shake = function (intShakes /*Amount of shakes*/, intDistance /*Shake distance*/, intDuration /*Time duration*/) {
		this.each(function () {
			var jqNode = $(this);
			jqNode.css({ position: 'relative' });
			for (var x = 1; x <= intShakes; x++) {
				jqNode.animate({ left: (intDistance * -1) }, (((intDuration / intShakes) / 4)))
					.animate({ left: intDistance }, ((intDuration / intShakes) / 2))
					.animate({ left: 0 }, (((intDuration / intShakes) / 4)));
			}
		});
		return this;
	};

	$(window).scroll(function () {
		var pagename = $(".topnav").attr("pagename");
		var objtop;
		if (pagename == "home") {
			objtop = $(".welcome_block").height();
			objtop *= 0.3;
		}
		if (pagename == "search") {
			objtop = $(".web_name").height();
			objtop *= 0.5;
		}
		if ($(window).scrollTop() > objtop) {
			if (!$(".topnav").hasClass("top_float"))
				$(".topnav").addClass("top_float");
		}
		else {
			if ($(".topnav").hasClass("top_float"))
				$(".topnav").removeClass("top_float");
		}
	});

	function getByteLen(val) {
		var len = 0;
		for (var i = 0; i < val.length; i++) {
			var a = val.charAt(i);
			if (a.match(/[^\x00-\xff]/ig) !== null) {
				len += 2;
			}
			else {
				len += 1;
			}
		}
		return len;
	}
	function login_input_check_len() {
		if (getByteLen($("#login_input").val()) > 20) {
			$("#login_error_message").html("邮箱或UID过长");
			$("#login_input").shake(10, 10, 500);
			return 0;
		}
		if (getByteLen($("#password_input").val()) > 20) {
			$("#login_error_message").html("密码过长");
			$("#password_input").shake(10, 10, 500);
			return 0;
		}
		$("#login_error_message").html("");
		return 1;
	}
	function login_input_check_empty() {
		if (getByteLen($("#login_input").val()) == 0) {
			$("#login_error_message").html("邮箱或UID不能为空");
			$("#login_input").shake(10, 10, 500);
			return 0;
		}
		if (getByteLen($("#password_input").val()) == 0) {
			$("#login_error_message").html("密码不能为空");
			$("#password_input").shake(10, 10, 500);
			return 0;
		}
		$("#login_error_message").html("");
		return 1;
	}
	$(".my_checkbox").click(function () {
		var $tmp = $(".my_checkbox");
		if ($tmp.attr("value") == "0") {
			$(".checkbox_icon").html("check_box");
			$tmp.attr("value", "1");
		}
		else {
			$(".checkbox_icon").html("check_box_outline_blank");
			$tmp.attr("value", "0");
		}
	})

	function tag_init() {
		var $tmp = $(".tag");
		for (var i = 0; i < $tmp.length; ++i)
			if ($($tmp[i]).attr("value") == "1") {
				if (!$($tmp[i]).hasClass("glass_effect" + glass_effect_kind))
					$($tmp[i]).addClass("glass_effect" + glass_effect_kind);
			}
			else
				if ($($tmp[i]).hasClass("glass_effect" + glass_effect_kind))
					$($tmp[i]).removeClass("glass_effect" + glass_effect_kind);
	}
	tag_init();

	function tag_click(obj, k = '') {
		var $tmp = $(obj);
		$tmp.toggleClass("glass_effect" + glass_effect_kind);
		if ($tmp.attr("value") == "0")
			$tmp.attr("value", "1");
		else
			$tmp.attr("value", "0");
	}
	$("#car_type [all]").click(function () {
		var $tmp = $(event.target);
		tag_click($tmp.get(0));
		if ($("#car_type .tag[all]").attr("value") == "1") {
			$("#car_type .tag[value='1']").attr("value", "0");
			$("#car_type .tag[all]").attr("value", "1");
			tag_init();
		}
		filter();
	})

	$("#date_type [all]").click(function () {
		var $tmp = $(event.target);
		tag_click($tmp.get(0));
		if ($("#date_type .tag[all]").attr("value") == "1") {
			$("#date_type .tag[value='1']").attr("value", "0");
			$("#date_type .tag[all]").attr("value", "1");
			tag_init();
		}
		filter();
	})

	function tag_reset() {
		$("#car_type .tag:not([all])").remove();
		$("#car_type [all]").attr("value", "1");
		$("#date_type .tag:not([all])").remove();
		$("#date_type [all]").attr("value", "1");
		var $tmp = $(".search_result");
		var m = $tmp.length;
		if (m == 0) {
			if (!$("#empty_window").hasClass("search_window_disp"))
				$("#empty_window").addClass("search_window_disp");
			if ($("#tag_window").hasClass("search_window_disp"))
				$("#tag_window").removeClass("search_window_disp");
			return;
		}
		if ($("#empty_window").hasClass("search_window_disp"))
			$("#empty_window").removeClass("search_window_disp");
		if (!$("#tag_window").hasClass("search_window_disp"))
			$("#tag_window").addClass("search_window_disp");
		var list = new Array(m);
		if ($(".topnav").attr("pagename") == "login")
			for (var i = 0; i < m; ++i)
				list[i] = ($($tmp.get(i))).attr("date_tag");
		else
			for (var i = 0; i < m; ++i)
				list[i] = ($($tmp.get(i))).attr("kind_tag");
		$.unique(list.sort());
		m = list.length;
		if ($(".topnav").attr("pagename") == "login")
			for (var i = 0; i < m; ++i)
				$("#date_type").append('<div class="tag" value="0">' + list[i] + '</div>');
		else
			for (var i = 0; i < m; ++i)
				$("#car_type").append('<div class="tag" value="0">' + list[i] + '</div>');
		tag_init();
		$("#car_type .tag:not([all])").click(function () {
			var $tmp = $(event.target);
			tag_click($tmp.get(0));
			if ($("#car_type .tag[all]").attr("value") == "1")
				tag_click($("#car_type .tag[all]").get(0));
			filter();
		})
		$("#date_type .tag:not([all])").click(function () {
			var $tmp = $(event.target);
			tag_click($tmp.get(0));
			if ($("#date_type .tag[all]").attr("value") == "1")
				tag_click($("#date_type .tag[all]").get(0));
			filter();
		})
		filter();
	}


	$("form[login] input").keypress(function () {
		if (event.which == 13) {
			var inputs = $("form[login]").find("input");
			var idx = inputs.index(this);
			if (idx != inputs.length - 1) {
				inputs[idx + 1].focus();
				inputs[idx + 1].select();
			}
			else
				$("#login_button").click();
		}
	});
	$("#change_info input").keypress(function () {
		if (event.which == 13) {
			var inputs = $("#change_info").find("input");
			var idx = inputs.index(this);
			if (idx != inputs.length - 1) {
				inputs[idx + 1].focus();
				inputs[idx + 1].select();
			}
			else
				$("#edit1").click();
		}
	});
	$("#change_pwd input").keypress(function () {
		if (event.which == 13) {
			var inputs = $("#change_pwd").find("input");
			var idx = inputs.index(this);
			if (idx != inputs.length - 1) {
				inputs[idx + 1].focus();
				inputs[idx + 1].select();
			}
			else
				$("#edit2").click();
		}
	});
	$("#edit1").click(function(){
		$.post("/modify_info", {name: $("#modify_name_input").val(), phone: $("#modify_phone_input").val()}, function (data) {
			if(!data.result) {
				$.Pro("修改失败", {BoxBgopacity:0.6});
			}
			else
				$.Pro("修改成功", {BoxBgopacity:0.6});
		});
	})
	$("#edit2").click(function(){
		$.post("/modify_pwd", {pw1: $("#modify_password_old").val(), pw2: $("#modify_password_new").val(), pw3: $("#modify_password_rep").val()}, function (data) {
			if(!data.result) {
				$.Pro("修改失败", {BoxBgopacity:0.6});
			}
			else
				$.Pro("修改成功", {BoxBgopacity:0.6});
		});
	})
	$("form[register] input").keypress(function (e) {
		if (e.which == 13) {
			var inputs = $("form[register]").find("input");
			var idx = inputs.index(this);
			if (idx != inputs.length - 1) {
				inputs[idx + 1].focus();
				inputs[idx + 1].select();
			}
			else
				$("#register_button2").click();
		}
	});
	$("#login_input, #password_input").blur(login_input_check_len);
	$("#login_button").click(function () {
		if (login_input_check_len() && login_input_check_empty()) {
			$.post("/login", { name: $("#login_input").val(), password: $("#password_input").val() }, function (data) {
				if (!data.result) {
					$("#login_error_message").html(data.message);
					$("#login_input, #password_input").shake(10, 10, 500);
				}
				else {
					$("#user_name").html(data.message);
					$(".mask").fadeOut();
					$(".login_window").css("top", "-400px");
					$(".login_window").css("opacity", "0");
					$(".login_window").css("visibility", "hidden");
					$("#user_button").addClass("logged");
				}
			});
		}
	});
	$("#register_button2").click(function () {
		$.post("/register", { name: $("#register_name").val(), password: $("#register_password").val(), email: $("#register_email").val(), phone: $("#register_mobile").val() }, function (data) {
			if (!data.result) {
				$("#login_error_message3").html(data.message);
				$("#login_input, #password_input").shake(10, 10, 500);
			}
			else {
				$("#return_to_login_window").click();
				$.Pro('注册成功！您的UID是' + data.message, {BoxBgopacity:0.6});
			}
		});
	});
	$("#register_button").click(function () {
		$(".login_window").css("visibility", "hidden");
		$(".register_window").css("visibility", "visible");
		$(".login_window").addClass("rot180");
		$(".register_window").addClass("rot0");
	});
	$("#return_to_login_window").click(function () {
		$(".login_window").css("visibility", "visible");
		$(".login_window").removeClass("rot180");
		$(".register_window").removeClass("rot0");
		$(".register_window").css("visibility", "hidden");
	})
	$("#user_button").click(function () {
		if (!$("#user_button").hasClass("logged")) {
			$(".mask").fadeIn();
			$(".login_window").css("top", "0px");
			$(".login_window").css("visibility", "visible");
			$(".login_window").css("opacity", "1");
		}
		else
			$(".user_menu").toggleClass("user_menu_display");
	});
	$(".shrink_button").click(function () {
		$(".user_menu").toggleClass("user_menu_display");
	})
	$("#login_window_close").click(function () {
		$(".mask").fadeOut();
		$(".login_window").css("top", "-400px");
		$(".login_window").css("opacity", "0");
		$(".login_window").css("visibility", "hidden");
		$(".register_window").css("visibility", "hidden");
	});
	function find_avail(ob) {
		while (!$(ob).hasClass('available'))
			ob = ob.parentNode;
		return ob;
	}
	function buy_option_resp(ob) {
		if (!$(ob).hasClass('active')) {
			$(ob).addClass('active');
			$(ob).next().addClass('buy_option_slip_right');
			$(ob).next().removeClass('buy_option_slip_left');
		}
		else {
			$(ob).removeClass('active');
			$(ob).next().addClass('buy_option_slip_left');
			$(ob).next().removeClass('buy_option_slip_right');
		}
	}
	var check_ticket_html = [
	];
	var ticket_html1 = [
		'<div class="w3-card glass_effect search_result">',
		' <div class="ticket_info" >',
		'   <div class="time_used_info"></div>',
		'   <div class="train_id_info">',
		'     <div class="train_id"></div>',
		'     <div class="train_id_2"></div>',
		'   </div>',
		'   <div class="time_info">',
		'     <div class="starting_station">',
		'       <time></time>',
		'       <div class="station_name"></div>',
		'     </div>',
		'     <div class="link_symbol">&rarr;</div>',
		'     <div class="ending_station">',
		'       <time></time>',
		'       <div class="station_name"></div>',
		'     </div>',
		'   </div>',
		'   <div class="seat_contain">',
		'     <div class="seat_contain_text">',
		'       <div class="buy_text_1">最低价</div>',
		'       <div class="buy_text_2"> <span class="buy_text_2_1">￥</span><span class="buy_text_2_2 pri"></span> </div>',
		'       <div class="buy_text_3"></div>',
		'     </div>',
		'   </div>',
		'   <div class="ver_line"></div>',
		'   <div class="seat_contain_list">',
		'   </div>',
		'   </div>',
		'  <div class="train_info">',
		'   <div class="time_used_info"></div>',
		'   <div style="overflow: hidden; display: inline-flex; background-color: rgba(236, 236, 236, 0.8); flex: 1 1 auto">',
		'    <div class="train_info_contain">',
		'     <div class="train_id_info_detail"> <img src="../static/icon/ic_directions_railway_black_48dp.png" align="middle" alt="train" height="20px"></div>',
		'     <div class="station_detail">',
		'       <div class="starting_station">',
		'         </div>',
		'       <div class="link_symbol">&rarr;</div>',
		'       <div class="ending_station">',
		'         </div>',
		'     </div>',
		'   </div>',
		'   <div class="ver_line"></div>',
		'   <div class="station_list">',
		'   </div>',
		'   </div>',
		'   </div>',
	];
	var ticket_html2 = [
		'     <div class="seat_contain">',
		'       <div class="seat_contain_text">',
		'         <div class="buy_text_1"></div>',
		'         <div class="buy_text_2"> <span class="buy_text_2_1"></span><span class="buy_text_2_2"></span></div>',
		'         <div class="buy_text_3"></div>',
		'       </div>',
		'       <div class="buy_option">',
		'         <center>',
		'           <button class="w3-button buy_text_4">购买</button>',
		'           <br>',
		'           <input class="w3-input buy_text_5" type="tel" value="1" min="1" max="10" style="width:60%; border-style: none">',
		'           <hr style="width: 30%; position: relative;  top: -18px;">',
		'           <button type="button" class="buy_text_6">&#60;</button>',
		'         </center>',
		'       </div>',
		'     </div>'
	];
	var ticket_html3 = [
		'     <div class="station_contain">',
		'       <div class="station_text_1"></div>',
		'       <div class="station_text_2"><span style="font-size: 13px"></span></div>',
		'       <div class="station_text_3"></div>',
		'     </div>'
	]

	function get_minute(t) {
		var ans = 0;
		ans += (t.charAt(0) - '0') * 600;
		ans += (t.charAt(1) - '0') * 60;
		ans += (t.charAt(3) - '0') * 10;
		ans += (t.charAt(4) - '0') * 1;
		return ans;
	}

	function get_time(t1, t2) {
		var ans = get_minute(t2) - get_minute(t1);
		if (ans < 0)
			ans += 24 * 60;
		var re = '';
		re = re + Math.floor(ans / 600);
		ans %= 600;
		re = re + Math.floor(ans / 60) + ':';
		ans %= 60;
		re = re + Math.floor(ans / 10);
		ans %= 10;
		re = re + ans;
		return re;
	}

	function bind_click(s) {
		$(s + " .buy_option_slip_left").removeClass("buy_option_slip_left");
		$(s + " .buy_option_slip_right").removeClass("buy_option_slip_right");
		$(s + " .seat_contain .active").removeClass("active");
		$(s + " .available").hover(function () {
			ob = find_avail(event.target);
			$(ob).addClass('hover');
		}, function () {
			ob = find_avail(event.target);
			$(ob).removeClass('hover');
		});
		$(s + " .buy_text_6").click(function () {
			ob = event.target;
			while (!$(ob).hasClass('seat_contain'))
				ob = ob.parentNode;
			ob = ob.firstChild;
			while (!$(ob).hasClass('available'))
				ob = $(ob).next().get(0);
			buy_option_resp(ob);
		});
		$(s + " .available").click(function () {
			ob = find_avail(event.target);
			buy_option_resp(ob);
		});
		$(s + " .train_id_info").click(function () {
			ob = event.target;
			while (!$(ob).hasClass('ticket_info'))
				ob = ob.parentNode;
			$(ob).next().slideToggle(200);
		});
		$(s + " .buy_text_4").click(function () {
			if (!$("#user_button").hasClass("logged")) {
				$.Pro("请先登录");
				$("#user_button").click();
				return;
			}
			var $tmp = $(event.target);
			var $p2 = $tmp.closest('.seat_contain');
			var $p1 = $tmp.closest('.search_result');
			if ($(".topnav").attr("pagename") != "login")
				$.Pop('<div style="text-align: left">' +
					'<h5>车次：' + $p1.find('.train_id_2').html() + '</h5>' +
					'<h5>始发站：' + $p1.attr('st_tag') + '(' + $p1.find('.starting_station time').html() + ')' + '</h5>' +
					'<h5>终点站：' + $p1.attr('ar_tag') + '(' + $p1.find('.ending_station time').html() + ')' + '</h5>' +
					'<h5>日期：' + $p1.attr('date_tag') + '</h5>' +
					'<h5>种类：' + $p2.find('.buy_text_1').html() + '</h5>' +
					'<h5>数量：' + $p2.find('.buy_text_5').val() + '张</h5>' +
					'</div>', 'confirm_ticket', function () {
						$.post("/buy_ticket", {
							train_id: $p1.attr('train_id_tag'),
							loc1: $p1.attr('st_tag'), loc2: $p1.attr('ar_tag'), date: $p1.attr('date_tag'),
							num: $p2.find('.buy_text_5').val(), ticket_kind: $p2.find('.buy_text_1').html()
						}, function (data) {
							$.Pro(data.message)
						});
					});
			else
				$.Pop('<div style="text-align: left">' +
					'<h5>车次：' + $p1.find('.train_id_2').html() + '</h5>' +
					'<h5>始发站：' + $p1.attr('st_tag') + '(' + $p1.find('.starting_station time').html() + ')' + '</h5>' +
					'<h5>终点站：' + $p1.attr('ar_tag') + '(' + $p1.find('.ending_station time').html() + ')' + '</h5>' +
					'<h5>日期：' + $p1.attr('date_tag') + '</h5>' +
					'<h5>种类：' + $p2.find('.buy_text_1').html() + '</h5>' +
					'<h5>数量：' + $p2.find('.buy_text_5').val() + '张</h5>' +
					'</div>', 'td_ticket', function () {
						$.post("/td_ticket", {
							train_id: $p1.attr('train_id_tag'),
							loc1: $p1.attr('st_tag'), loc2: $p1.attr('ar_tag'), date: $p1.attr('date_tag'),
							num: $p2.find('.buy_text_5').val(), ticket_kind: $p2.find('.buy_text_1').html()
						}, function (data) {
							$.Pro(data.message)
						});
					});
		});
	}

	function ticket_sort() {
		var $sort_list = $("#display_container .search_result");
		$sort_list.sort(function (a, b) {
			$key_word = $(".sort_key .tag[value='1']");
			var ans;
			if ($key_word.attr("id") == "leaving_time") {
				if ($(a).find(".starting_station time").html() < $(b).find(".starting_station time").html())
					ans = 1;
				if ($(a).find(".starting_station time").html() == $(b).find(".starting_station time").html())
					ans = 0;
				if ($(a).find(".starting_station time").html() > $(b).find(".starting_station time").html())
					ans = -1;
			}
			if ($key_word.attr("id") == "date_time") {
				var ta = $(a).find("")
				if ($(a).attr("date_tag") < $(b).attr("date_tag"))
					ans = 1;
				if ($(a).attr("date_tag") == $(b).attr("date_tag")) {
					if ($(a).find(".starting_station time").html() < $(b).find(".starting_station time").html())
						ans = 1;
					if ($(a).find(".starting_station time").html() == $(b).find(".starting_station time").html())
						ans = 0;
					if ($(a).find(".starting_station time").html() > $(b).find(".starting_station time").html())
						ans = -1;
				}
				if ($(a).attr("date_tag") > $(b).attr("date_tag"))
					ans = -1;
			}
			if ($key_word.attr("id") == "arriving_time") {
				if ($(a).find(".ending_station time").html() < $(b).find(".ending_station time").html())
					ans = 1;
				if ($(a).find(".ending_station time").html() == $(b).find(".ending_station time").html())
					ans = 0;
				if ($(a).find(".ending_station time").html() > $(b).find(".ending_station time").html())
					ans = -1;
			}
			if ($key_word.attr("id") == "used_time") {
				var ta = get_time($(a).find(".starting_station time").html(), $(a).find(".ending_station time").html());
				var tb = get_time($(b).find(".starting_station time").html(), $(b).find(".ending_station time").html());
				if (ta < tb)
					ans = 1;
				if (ta == tb)
					ans = 0;
				if (ta > tb)
					ans = -1;
			}
			if ($key_word.attr("id") == "price") {
				if (Number($(a).find(".pri").html()) < Number($(b).find(".pri").html()))
					ans = 1;
				if (Number($(a).find(".pri").html()) == Number($(b).find(".pri").html()))
					ans = 0;
				if (Number($(a).find(".pri").html()) > Number($(b).find(".pri").html()))
					ans = -1;
			}
			if ($("#inc").attr("value") == '1')
				ans = -ans;
			return ans;
		});
		$("#display_container").append($sort_list);
	}

	var $all;
	function filter() {
		var $tag;
		if ($(".topnav").attr("pagename") == "login")
			$tag = $("#date_type .tag[value='1']");
		else
			$tag = $("#car_type .tag[value='1']");
		var n = $tag.length;
		$("#display_container").empty();
		$("#result").empty();
		if (n == 1 && typeof ($tag.attr("all")) != "undefined") {
			$("#display_container").html($all);
			bind_click('#display_container');
			ticket_sort();
			return;
		}
		$("#result").html($all);
		if ($(".topnav").attr("pagename") == "login")
			for (var i = 0; i < n; ++i)
				$("#display_container").append($("#result").find("[date_tag='" + $($tag.get(i)).html() + "']"));
		else
			for (var i = 0; i < n; ++i)
				$("#display_container").append($("#result").find("[kind_tag='" + $($tag.get(i)).html() + "']"));
		bind_click('#display_container');
		ticket_sort();
	}

	$("#dec").click(function () {
		tag_click($("#inc").get(0));
		tag_click($("#dec").get(0));
		filter();
	})
	$("#inc").click(function () {
		tag_click($("#inc").get(0));
		tag_click($("#dec").get(0));
		filter();
	})

	$(".sort_key .tag").click(function () {
		var $tmp = $(event.target);
		if ($tmp.attr("value") == '1')
			return;
		tag_click($(".sort_key .tag[value='1']").get(0));
		tag_click($tmp.get(0));
		filter();
	})

	$(".search_button").click(function () {
		$.post("/search", { loc1: $("#start_s").val(), loc2: $("#end_s").val(), date: $("#start_date").val() }, function (data) {
			var num = data.length;
			$(".search_result").remove();
			for (var i = 0; i < num; ++i) {
				$("#tmp").html(ticket_html1.join(''));
				$("#tmp .search_result").attr("kind_tag", data[i].kind_tag);
				$("#tmp .train_id").html(data[i].kind);
				$("#tmp .train_id_2").html(data[i].name);
				$("#tmp .starting_station time").html(data[i].dep_time);
				$("#tmp .ending_station time").html(data[i].des_time);
				$("#tmp .starting_station .station_name").html(data[i].dep);
				$("#tmp .search_result").attr("date_tag", data[i].date);
				$("#tmp .search_result").attr("st_tag", data[i].dep);
				$("#tmp .search_result").attr("train_id_tag", data[i].train_id);
				$("#tmp .search_result").attr("ar_tag", data[i].des);
				if (data[i].dep == data[i].station[0])
					$("#tmp .starting_station .station_name").prepend('始 ');
				$("#tmp .ending_station .station_name").html(data[i].des);
				if (data[i].des == data[i].station[data[i].station.length - 1])
					$("#tmp .ending_station .station_name").append(' 终');
				if (get_minute(data[i].dep_time) > get_minute(data[i].des_time))
					$("#tmp .ending_station time").append('<span style="font-size: 13px; letter-spacing: -3px">+1</span>');
				var min = 1000000000;
				var m = data[i].price.length;
				for (var j = 0; j < m; ++j) {
					$("#tmp .seat_contain_list").append(ticket_html2.join(''));
					if (typeof (data[i].price[j]) != 'string')
						min = Math.min(min, data[i].price[j]);
				}
				$("#tmp .buy_text_2_2").html('' + min);
				var $seats = $("#tmp .seat_contain_list").find(".seat_contain");
				for (var j = 0; j < m; ++j) {
					var $now = $($seats.get(j));
					$now.attr("rem_tag", data[i].remain[j]);
					$now.attr("name_tag", data[i].seat_name[j]);
					$now.find(".buy_text_1").html(data[i].seat_name[j]);
					$now.find(".buy_text_2_2").html(data[i].price[j]);
					if (data[i].remain[j] != -1) {
						$now.find(".buy_text_2_1").html('￥');
						if (data[i].remain[j] > 0)
							$now.find(".seat_contain_text").addClass("available");
						if (data[i].remain[j] <= 20)
							$now.find(".buy_text_3").html('余' + data[i].remain[j] + '张');
					}
				}
				m = data[i].station.length;
				$("#tmp .train_id_info_detail").append(data[i].name + ' | 全程' + get_time(data[i].arr_time[0], data[i].arr_time[m - 1]) + ' | 此程' + get_time(data[i].dep_time, data[i].des_time));
				$("#tmp .station_detail .starting_station").html(data[i].station[0] + '<br>' + data[i].arr_time[0]);
				$("#tmp .station_detail .ending_station").html(data[i].station[m - 1] + '<br>' + data[i].arr_time[m - 1]);
				if (get_minute(data[i].arr_time[0]) > get_minute(data[i].arr_time[m - 1]))
					$("#tmp .station_detail .ending_station").append('<span style="font-size: 13px;">+1</span>');
				for (var j = 0; j < m; ++j)
					$("#tmp .station_list").append(ticket_html3.join(''));
				var $station = $("#tmp .station_contain");
				for (var j = 0; j < m; ++j) {
					var $now = $($station.get(j));
					$now.find(".station_text_1").html(data[i].station[j]);
					$now.find(".station_text_2").prepend(data[i].arr_time[j]);
					$now.find(".station_text_3").html(data[i].stan_time[j]);
					if (get_minute(data[i].arr_time[j]) < get_minute(data[i].arr_time[0]))
						$now.find("span").html('+1');
				}
				$("#result").append($("#tmp .search_result"));
			}
			$all = $(".search_result");
			$(".train_info").hide();
			tag_reset();
		});
	})
});

/* Toggle between adding and removing the "responsive" class to topnav when the user clicks on the icon */
function myFunction() {
	var x = document.getElementById("myTopnav");
	if (x.className === "topnav") {
		x.className += " responsive";
	} else {
		x.className = "topnav";
	}
} 
