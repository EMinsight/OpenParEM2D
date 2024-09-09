// Control
//   build=diffPair
//   check_limits=true
// EndControl
// Strip
//    name=diffPair
//    use_symmetry=false
//    upper_material=air
//    upper_thickness=0.006
//    lower_material=alumina
//    lower_thickness=0.000635
//    left_side_gap=0.0085
//    right_side_material=PMC
//    right_side_gap=0.0005
//    trace_thickness=0.0003
//    trace_width=0.001
//    trace_etch_angle=90
//    default_conductor_material=PEC
// EndStrip
Point(1) = {-0.009,0,0,0.00165875};
Point(2) = {-0.001135,0,0,0.00165875};
Point(3) = {-0.0005,0,0,0.000635};
Point(4) = {0,0,0,0.000635};
Point(5) = {0.0005,0,0,0.000635};
Point(6) = {0.00075,0,0,0.00165875};
Point(7) = {0.001,0,0,0.00165875};
Point(8) = {-0.009,0.000635,0,0.00165875};
Point(9) = {-0.000833333333333333,0.000635,0,0.00165875};
Point(10) = {-0.000666666666666667,0.000635,0,0.0003};
Point(11) = {-0.0005,0.000635,0,0.0003};
Point(12) = {-0.000333333333333333,0.000635,0,0.0003};
Point(13) = {-0.000166666666666667,0.000635,0,0.000635};
Point(14) = {0,0.000635,0,0.000635};
Point(15) = {0.000166666666666667,0.000635,0,0.000635};
Point(16) = {0.000333333333333333,0.000635,0,0.0003};
Point(17) = {0.0005,0.000635,0,0.0003};
Point(18) = {0.000666666666666667,0.000635,0,0.0003};
Point(19) = {0.000833333333333333,0.000635,0,0.00165875};
Point(20) = {0.001,0.000635,0,0.00165875};
Point(21) = {-0.0005,0.000935,0,0.0003};
Point(22) = {-0.000333333333333333,0.000935,0,0.0003};
Point(23) = {-0.000166666666666667,0.000935,0,0.000635};
Point(24) = {0,0.000935,0,0.000635};
Point(25) = {0.000166666666666667,0.000935,0,0.000635};
Point(26) = {0.000333333333333333,0.000935,0,0.0003};
Point(27) = {0.0005,0.000935,0,0.0003};
Point(28) = {-0.009,0.006635,0,0.00165875};
Point(29) = {0,0.006635,0,0.00165875};
Point(30) = {0.001,0.006635,0,0.00165875};
Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,5};
Line(5) = {5,6};
Line(6) = {6,7};
Line(7) = {1,8};
Line(8) = {7,20};
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
Line(30) = {20,30};
Line(31) = {28,29};
Line(32) = {29,30};
Curve Loop(1) = {1,2,3,4,5,6,8,-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-9,-7};
Plane Surface(1) = {1};
Curve Loop(2) = {9,10,11,21,23,24,25,26,27,28,-22,18,19,20,30,-32,-31,-29};
Plane Surface(2) = {2};
Physical Surface("alumina",1) = {1};
Physical Surface("air",2) = {2};
