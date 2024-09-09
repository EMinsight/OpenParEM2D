// Control
//   build=diffPair
//   check_limits=true
// EndControl
// CoupledStrip
//    name=diffPair
//    upper_material=air
//    solution_impedance_calculation=line
//    upper_thickness=0.006
//    lower_material=alumina
//    lower_thickness=0.000635
//    left_side_gap=0.0085
//    right_side_gap=0.0085
//    trace_left_width=0.001
//    trace_right_width=0.001
//    trace_thickness=0.0003
//    trace_air_gap=0.001
//    trace_etch_angle=90
//    default_conductor_material=PEC
// EndCoupledStrip
Point(1) = {-0.01,0,0,0.00165875};
Point(2) = {-0.002135,0,0,0.00165875};
Point(3) = {-0.0015,0,0,0.000635};
Point(4) = {-0.001,0,0,0.000635};
Point(5) = {-0.0005,0,0,0.000635};
Point(6) = {-0.00025,0,0,0.00165875};
Point(7) = {0,0,0,0.00165875};
Point(8) = {-0.01,0.000635,0,0.00165875};
Point(9) = {-0.00183333333333333,0.000635,0,0.00165875};
Point(10) = {-0.00166666666666667,0.000635,0,0.0003};
Point(11) = {-0.0015,0.000635,0,0.0003};
Point(12) = {-0.00133333333333333,0.000635,0,0.0003};
Point(13) = {-0.00116666666666667,0.000635,0,0.000635};
Point(14) = {-0.001,0.000635,0,0.000635};
Point(15) = {-0.000833333333333333,0.000635,0,0.000635};
Point(16) = {-0.000666666666666667,0.000635,0,0.0003};
Point(17) = {-0.0005,0.000635,0,0.0003};
Point(18) = {-0.000333333333333333,0.000635,0,0.0003};
Point(19) = {-0.000166666666666667,0.000635,0,0.00165875};
Point(20) = {0,0.000635,0,0.00165875};
Point(21) = {-0.0015,0.000935,0,0.0003};
Point(22) = {-0.00133333333333333,0.000935,0,0.0003};
Point(23) = {-0.00116666666666667,0.000935,0,0.000635};
Point(24) = {-0.001,0.000935,0,0.000635};
Point(25) = {-0.000833333333333333,0.000935,0,0.000635};
Point(26) = {-0.000666666666666667,0.000935,0,0.0003};
Point(27) = {-0.0005,0.000935,0,0.0003};
Point(28) = {-0.01,0.006635,0,0.00165875};
Point(29) = {-0.001,0.006635,0,0.00165875};
Point(30) = {0,0.006635,0,0.00165875};
Point(102) = {0.00025,0,0,0.00165875};
Point(103) = {0.0005,0,0,0.000635};
Point(104) = {0.001,0,0,0.000635};
Point(105) = {0.0015,0,0,0.000635};
Point(106) = {0.002135,0,0,0.00165875};
Point(107) = {0.01,0,0,0.00165875};
Point(109) = {0.000166666666666667,0.000635,0,0.00165875};
Point(110) = {0.000333333333333333,0.000635,0,0.0003};
Point(111) = {0.0005,0.000635,0,0.0003};
Point(112) = {0.000666666666666667,0.000635,0,0.0003};
Point(113) = {0.000833333333333333,0.000635,0,0.000635};
Point(114) = {0.001,0.000635,0,0.000635};
Point(115) = {0.00116666666666667,0.000635,0,0.000635};
Point(116) = {0.00133333333333333,0.000635,0,0.0003};
Point(117) = {0.0015,0.000635,0,0.0003};
Point(118) = {0.00166666666666667,0.000635,0,0.0003};
Point(119) = {0.00183333333333333,0.000635,0,0.00165875};
Point(120) = {0.01,0.000635,0,0.00165875};
Point(121) = {0.0005,0.000935,0,0.0003};
Point(122) = {0.000666666666666667,0.000935,0,0.0003};
Point(123) = {0.000833333333333333,0.000935,0,0.000635};
Point(124) = {0.001,0.000935,0,0.000635};
Point(125) = {0.00116666666666667,0.000935,0,0.000635};
Point(126) = {0.00133333333333333,0.000935,0,0.0003};
Point(127) = {0.0015,0.000935,0,0.0003};
Point(129) = {0.001,0.006635,0,0.00165875};
Point(130) = {0.01,0.006635,0,0.00165875};
Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,5};
Line(5) = {5,6};
Line(6) = {6,7};
Line(7) = {1,8};
Line(9) = {8,9};
Line(10) = {9,10};
Line(11) = {10,11};
Line(12) = {11,12};
Line(13) = {12,13};
Line(14) = {13,14};
Line(15) = {14,15};
Line(16) = {15,16};
Line(17) = {16,17};
Line(18) = {17,18};
Line(19) = {18,19};
Line(20) = {19,20};
Line(21) = {11,21};
Line(22) = {17,27};
Line(23) = {21,22};
Line(24) = {22,23};
Line(25) = {23,24};
Line(26) = {24,25};
Line(27) = {25,26};
Line(28) = {26,27};
Line(29) = {8,28};
Line(31) = {28,29};
Line(32) = {29,30};
Line(101) = {7,102};
Line(102) = {102,103};
Line(103) = {103,104};
Line(104) = {104,105};
Line(105) = {105,106};
Line(106) = {106,107};
Line(108) = {107,120};
Line(109) = {20,109};
Line(110) = {109,110};
Line(111) = {110,111};
Line(112) = {111,112};
Line(113) = {112,113};
Line(114) = {113,114};
Line(115) = {114,115};
Line(116) = {115,116};
Line(117) = {116,117};
Line(118) = {117,118};
Line(119) = {118,119};
Line(120) = {119,120};
Line(121) = {111,121};
Line(122) = {117,127};
Line(123) = {121,122};
Line(124) = {122,123};
Line(125) = {123,124};
Line(126) = {124,125};
Line(127) = {125,126};
Line(128) = {126,127};
Line(130) = {120,130};
Line(131) = {30,129};
Line(132) = {129,130};
Curve Loop(1) = {1,2,3,4,5,6,101,102,103,104,105,106,108,-120,-119,-118,-117,-116,-115,-114,-113,-112,-111,-110,-109,-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-9,-7};
Plane Surface(1) = {1};
Curve Loop(2) = {9,10,11,21,23,24,25,26,27,28,-22,18,19,20,109,110,111,121,123,124,125,126,127,128,-122,118,119,120,130,-132,-131,-32,-31,-29};
Plane Surface(2) = {2};
Physical Surface("alumina",1) = {1};
Physical Surface("air",2) = {2};
