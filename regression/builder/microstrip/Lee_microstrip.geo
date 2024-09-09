// Control
//   build=Lee_microstrip
//   check_limits=true
// EndControl
// Strip
//    name=Lee_microstrip
//    use_symmetry=false
//    upper_material=air
//    upper_thickness=0.00225
//    lower_material=Lee_semiconductor
//    lower_thickness=0.00025
//    left_side_gap=0.001125
//    right_side_gap=0.001125
//    trace_thickness=5e-05
//    trace_width=0.00025
//    trace_etch_angle=90
//    default_conductor_material=PEC
// EndStrip
Point(1) = {-0.00125,0,0,0.000625};
Point(2) = {-0.000375,0,0,0.000625};
Point(3) = {-0.000125,0,0,0.00025};
Point(4) = {0,0,0,0.00025};
Point(5) = {0.000125,0,0,0.00025};
Point(6) = {0.000375,0,0,0.000625};
Point(7) = {0.00125,0,0,0.000625};
Point(8) = {-0.00125,0.00025,0,0.000625};
Point(9) = {-0.000208333333333333,0.00025,0,0.000625};
Point(10) = {-0.000166666666666667,0.00025,0,5e-05};
Point(11) = {-0.000125,0.00025,0,5e-05};
Point(12) = {-8.33333333333333e-05,0.00025,0,5e-05};
Point(13) = {-4.16666666666667e-05,0.00025,0,0.00025};
Point(14) = {0,0.00025,0,0.00025};
Point(15) = {4.16666666666667e-05,0.00025,0,0.00025};
Point(16) = {8.33333333333333e-05,0.00025,0,5e-05};
Point(17) = {0.000125,0.00025,0,5e-05};
Point(18) = {0.000166666666666667,0.00025,0,5e-05};
Point(19) = {0.000208333333333333,0.00025,0,0.000625};
Point(20) = {0.00125,0.00025,0,0.000625};
Point(21) = {-0.000125,0.0003,0,5e-05};
Point(22) = {-8.33333333333333e-05,0.0003,0,5e-05};
Point(23) = {-4.16666666666667e-05,0.0003,0,0.00025};
Point(24) = {0,0.0003,0,0.00025};
Point(25) = {4.16666666666667e-05,0.0003,0,0.00025};
Point(26) = {8.33333333333333e-05,0.0003,0,5e-05};
Point(27) = {0.000125,0.0003,0,5e-05};
Point(28) = {-0.00125,0.0025,0,0.000625};
Point(29) = {0,0.0025,0,0.000625};
Point(30) = {0.00125,0.0025,0,0.000625};
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
Physical Surface("Lee_semiconductor",1) = {1};
Physical Surface("air",2) = {2};
