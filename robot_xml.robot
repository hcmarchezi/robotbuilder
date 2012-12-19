<robot>
    <name>"robot01"</name>

    <base_position_orientation>
        <cell row="0" column="0">1</cell>
        <cell row="0" column="1">0</cell>
        <cell row="0" column="2">0</cell>
        <cell row="0" column="3">0</cell>

        <cell row="1" column="0">0</cell>
        <cell row="1" column="1">1</cell>
        <cell row="1" column="2">0</cell>
        <cell row="1" column="3">0</cell>

        <cell row="2" column="0">0</cell>
        <cell row="2" column="1">0</cell>
        <cell row="2" column="2">1</cell>
        <cell row="2" column="3">0</cell>

        <cell row="3" column="0">0</cell>
        <cell row="3" column="1">0</cell>
        <cell row="3" column="2">0</cell>
        <cell row="3" column="3">1</cell>
    </base_position_orientation>

    <link_chain>
        <link file="/home/hcmarchezi/Documents/Projects/robotbuilder/base.linktype" angle="-1.99992"/>
        <link file="/home/hcmarchezi/Documents/Projects/robotbuilder/teste2.linktype" angle="2.0999"/>
        <link file="/home/hcmarchezi/Documents/Projects/robotbuilder/teste2.linktype" angle="6.2148e+065"/>
    </link_chain>

    <robot_trajectory>
        <via_point time="0">
            <link_position index="0" joint_position="1.5" joint_accelaration="0" />
            <link_position index="1" joint_position="1.6" joint_accelaration="0" />
            <link_position index="2" joint_position="0" joint_accelaration="-6.27744e+066" />
        </via_point>
        <via_point time="30">
            <link_position index="0" joint_position="0.3" joint_accelaration="0" />
            <link_position index="1" joint_position="-0.8" joint_accelaration="0" />
            <link_position index="2" joint_position="0" joint_accelararion="-6.27744e+066" />
        </via_point>
        <via_point time="60">
            <link_position index="0" joint_position="-2" joint_accelaration="0" />
            <link_position index="1" joint_position="2.1" joint_accelaration="0" />
            <link_position index="2" joint_position="0" joint_accelararion="-6.27744e+066"/>
        </via_point>
    </robot_trasjectory>

</robot>

