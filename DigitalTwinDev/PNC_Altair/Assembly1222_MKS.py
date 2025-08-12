# encoding: utf-8

from msolve import *

def createTheModel ():

  Model_0 = Model(
    label  = 'Assembly1222',
    output = 'Assembly1222',
  )

  Units_1 = Units(
    force  = 'NEWTON',
    length = 'METER',
    mass   = 'KILOGRAM',
    time   = 'SECOND',
  )

  Accgrav_1 = Accgrav(
    jgrav = -9.80665,
  )

  Integrator_1 = Integrator(
    error          = 0.001,
    hmax           = 0.001,
    dae_jacob_init = 1,
    kmax           = 5,
    maxit          = 4,
    pattern        = 'TFFFT',
    dae_index      = 3,
    dae_constr_tol = 1e-07,
  )

  Equilibrium_1 = Equilibrium(
    type                 = 'STATIC',
    skip_mkeam           = True,
    error                = 0.0001,
    maxit                = 50,
    imbalance            = 0.0001,
    kinetic_energy_error = 1e-05,
    stability            = 1e-10,
  )

  Output_1 = Output(
    req_angle_radians = True,
    capture_max_pd    = True,
    req_comment_only  = True,
    azero             = 0.0,
    dzero             = 0.0,
    fzero             = 0.0,
    vzero             = 0.0,
  )

  H3dOutput_1 = H3dOutput(
    save           = True,
    linear_anim    = False,
    format_type    = 'MODAL',
    stress_format  = 'TENSOR',
    strain_format  = 'TENSOR',
    capture_max_pd = True,
  )

  Part_1 = Part(
    id     = 1,
    label  = 'Ground Body',
    ground = True,
  )

  Marker_30101010 = Marker(
    id    = 30101010,
    label = 'Global Frame',
    part  = Part_1,
  )

  Part_2 = Part(
    id     = 2,
    label  = 'V2 10 DISC 1',
    qg     = Point (-0.2023200291903103, -0.126339913264247, -0.09401165486126471),
    reuler = Vector (-3.141587212855131, 1.5708017434874686, 1.575225010348801),
    mass   = 0.5855116363141984,
    ip     = [0.00041747144100921237, 0.0008047890951626463, 0.0004174714410206924, -5.183582849605778e-16, -1.6753245259504628e-15, 2.10731441076249e-09],
  )

  Marker_30102030 = Marker(
    id     = 30102030,
    part   = Part_2,
    qp     = Point (-0.010139708221518898, 0.16535090724068596, 0.14492292189281925),
    reuler = Vector (1.5663676432409923, 1.5708017434874686, -5.440734662032548e-06),
  )

  Request_1 = Request(
    id           = 1,
    label        = 'V2 10 DISC 1 - Kinetic Energy',
    type         = 'EXPRESSION',
    f2           = 'KE(2)',
    cnames       = ['', 'KE', '', '', '', '', '', ''],
    results_name = 'ke_output',
  )

  Request_2 = Request(
    id           = 2,
    label        = 'V2 10 DISC 1 - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30102030,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_3 = Request(
    id           = 3,
    label        = 'V2 10 DISC 1 - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30102030,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_4 = Request(
    id           = 4,
    label        = 'V2 10 DISC 1 - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30102030,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  External_301001 = External(
    id               = 301001,
    label            = 'V2_10_DISC_1 - CADGraphic',
    color            = '89:89:89',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_DISC_1'],
    refinement_level = 60,
  )

  Part_3 = Part(
    id    = 3,
    label = 'V2 10 TABLER  NEW 1',
    qg    = Point (-0.037015208528512235, -0.0332241580879678, -0.17981170000053134),
    mass  = 6.285646877146157,
    ip    = [0.013408169480210539, 0.02491452240441208, 0.017073766271337616, 0.002440646397215405, 0.0026695247970476964, 0.0003201779572115059],
  )

  Marker_30103050 = Marker(
    id   = 30103050,
    part = Part_3,
    qp   = Point (0.009921549036001696, 0.03884473187534592, 0.0629311267869638),
  )

  Request_5 = Request(
    id           = 5,
    label        = 'V2 10 TABLER  NEW 1 - Kinetic Energy',
    type         = 'EXPRESSION',
    f2           = 'KE(3)',
    cnames       = ['', 'KE', '', '', '', '', '', ''],
    results_name = 'ke_output',
  )

  Request_6 = Request(
    id           = 6,
    label        = 'V2 10 TABLER  NEW 1 - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30103050,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_7 = Request(
    id           = 7,
    label        = 'V2 10 TABLER  NEW 1 - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30103050,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_8 = Request(
    id           = 8,
    label        = 'V2 10 TABLER  NEW 1 - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30103050,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  External_301002 = External(
    id               = 301002,
    label            = 'V2_10_TABLER__NEW_1 - CADGraphic',
    color            = '38:38:38',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_TABLER__NEW_1'],
    refinement_level = 60,
  )

  Part_4 = Part(
    id    = 4,
    label = 'Rigid Group 1',
    qg    = Point (-0.005152305792945482, 0.04147542635658193, 0.1291612015911282),
    mass  = 3.5573622421551607,
    ip    = [0.007721311815202153, 0.007372684605901906, 0.002511847768321762, -8.67851726586906e-05, -7.130844869278982e-05, 0.00048656681932830975],
  )

  Marker_30104070 = Marker(
    id   = 30104070,
    part = Part_4,
  )

  Request_9 = Request(
    id           = 9,
    label        = 'Rigid Group 1 - Kinetic Energy',
    type         = 'EXPRESSION',
    f2           = 'KE(4)',
    cnames       = ['', 'KE', '', '', '', '', '', ''],
    results_name = 'ke_output',
  )

  Request_10 = Request(
    id           = 10,
    label        = 'Rigid Group 1 - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30104070,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_11 = Request(
    id           = 11,
    label        = 'Rigid Group 1 - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30104070,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_12 = Request(
    id           = 12,
    label        = 'Rigid Group 1 - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30104070,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  External_302003 = External(
    id               = 302003,
    label            = 'Tool_1 - CADGraphic',
    color            = '153:153:153',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['Tool_1'],
    refinement_level = 60,
  )

  External_302004 = External(
    id               = 302004,
    label            = 'V2_10_SPINDLE109_1_2 - CADGraphic',
    color            = '255:255:255',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_SPINDLE109_1_2'],
    refinement_level = 60,
  )

  External_302005 = External(
    id               = 302005,
    label            = 'V2_10_SPINDLE109_1_1 - CADGraphic',
    color            = '255:255:255',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_SPINDLE109_1_1'],
    refinement_level = 60,
  )

  External_302006 = External(
    id               = 302006,
    label            = 'V2_10_SPINDLE109_1 - CADGraphic',
    color            = '38:38:38',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_SPINDLE109_1'],
    refinement_level = 60,
  )

  Marker_30204080 = Marker(
    id   = 30204080,
    part = Part_4,
    qp   = Point (0.005152305792945482, -0.04147542635658193, -0.1291612015911282),
  )

  Marker_30204090 = Marker(
    id   = 30204090,
    part = Part_4,
    qp   = Point (0.005152305792945482, -0.04147542635658193, -0.1291612015911282),
  )

  Marker_30204100 = Marker(
    id   = 30204100,
    part = Part_4,
    qp   = Point (0.005152305792945482, -0.04147542635658193, -0.1291612015911282),
  )

  Marker_30204110 = Marker(
    id   = 30204110,
    part = Part_4,
    qp   = Point (0.005152305792945482, -0.04147542635658193, -0.1291612015911282),
  )

  Part_5 = Part(
    id     = 5,
    label  = 'V2 10  VERT 1',
    qg     = Point (-0.1232624373817584, -0.08201145796415824, -0.13671549999953253),
    reuler = Vector (-1.5707963267948932, 1.570796326794892, 1.5707963267948821),
    mass   = 4.133019904925918,
    ip     = [0.02144475976142374, 0.012331034976848157, 0.00969783325503604, 2.5072040577083594e-05, -4.886580818873651e-06, -0.0019491080087550112],
  )

  Marker_30105130 = Marker(
    id     = 30105130,
    part   = Part_5,
    qp     = Point (0.02291561579639144, 0.1271069388184748, -0.1756219684655145),
    reuler = Vector (1.5707963267949112, 1.570796326794892, -1.5707963267949),
  )

  Request_13 = Request(
    id           = 13,
    label        = 'V2 10  VERT 1 - Kinetic Energy',
    type         = 'EXPRESSION',
    f2           = 'KE(5)',
    cnames       = ['', 'KE', '', '', '', '', '', ''],
    results_name = 'ke_output',
  )

  Request_14 = Request(
    id           = 14,
    label        = 'V2 10  VERT 1 - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30105130,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_15 = Request(
    id           = 15,
    label        = 'V2 10  VERT 1 - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30105130,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_16 = Request(
    id           = 16,
    label        = 'V2 10  VERT 1 - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30105130,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  External_301007 = External(
    id               = 301007,
    label            = 'V2_10__VERT_1 - CADGraphic',
    color            = '89:89:89',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10__VERT_1'],
    refinement_level = 60,
  )

  Part_6 = Part(
    id     = 6,
    label  = 'V2 10 CARRAGE107X 1',
    qg     = Point (-0.008344388255267256, -0.06510201385645234, 0.0605135601631119),
    reuler = Vector (3.141592653589793, 1.5707963267948968, 3.141592653589793),
    mass   = 4.064160611191363,
    ip     = [0.012695275770271144, 0.014295207357375347, 0.005479930924487784, 0.001230598759761303, 0.0008446350775820144, 0.0011113774736367348],
  )

  Marker_30106150 = Marker(
    id     = 30106150,
    part   = Part_6,
    qp     = Point (0.0372147791750792, -0.011910799231971275, 0.07054240459885),
    reuler = Vector (1.2246467991473532e-16, 1.5707963267948968, 1.2246467991473532e-16),
  )

  Request_17 = Request(
    id           = 17,
    label        = 'V2 10 CARRAGE107X 1 - Kinetic Energy',
    type         = 'EXPRESSION',
    f2           = 'KE(6)',
    cnames       = ['', 'KE', '', '', '', '', '', ''],
    results_name = 'ke_output',
  )

  Request_18 = Request(
    id           = 18,
    label        = 'V2 10 CARRAGE107X 1 - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30106150,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_19 = Request(
    id           = 19,
    label        = 'V2 10 CARRAGE107X 1 - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30106150,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_20 = Request(
    id           = 20,
    label        = 'V2 10 CARRAGE107X 1 - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30106150,
    j            = Marker_30101010,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  External_301008 = External(
    id               = 301008,
    label            = 'V2_10_CARRAGE107X_1 - CADGraphic',
    color            = '89:89:89',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_CARRAGE107X_1'],
    refinement_level = 60,
  )

  External_301009 = External(
    id               = 301009,
    label            = 'V2_10_BASER_108_1 - CADGraphic',
    color            = '38:38:38',
    file             = 'C:/Kibira/VC2-50/Assembly1222_MKS.x_t',
    element          = ['V2_10_BASER_108_1'],
    refinement_level = 60,
  )

  Bushing_301001 = Bushing(
    id = 301001,
    c  = [2500000.0, 2500000.0, 0.0],
    ct = [5000000.0, 5000000.0, 5000000.0],
    k  = [50000000.0, 50000000.0, 0.0],
    kt = [100000000.0, 100000000.0, 100000000.0],
  )

  Marker_30106160 = Marker(
    id     = 30106160,
    part   = Part_6,
    qp     = Point (0.02085145087325572, -0.0167514897765786, 0.04578991909623213),
    reuler = Vector (1.5707963267948968, 1.5707963267948966, 2.220446049250313e-16),
  )

  Marker_30101160 = Marker(
    id     = 30101160,
    part   = Part_1,
    qp     = Point (0.012507062617988465, -0.019312094760220208, 0.07726504993969048),
    reuler = Vector (1.5707963267948966, 1.5707963267948966, -1.5707963267948966),
  )

  Request_21 = Request(
    id           = 21,
    label        = 'Joint 1 - TRANSLATIONAL - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30106160,
    j            = Marker_30101160,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_22 = Request(
    id           = 22,
    label        = 'Joint 1 - TRANSLATIONAL - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30106160,
    j            = Marker_30101160,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_23 = Request(
    id           = 23,
    label        = 'Joint 1 - TRANSLATIONAL - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30106160,
    j            = Marker_30101160,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_24 = Request(
    id           = 24,
    label        = 'Joint 1 - TRANSLATIONAL - FORCE',
    type         = 'FORCE',
    i            = Marker_30106160,
    j            = Marker_30101160,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_301001 = Sensor(
    id              = 301001,
    label           = 'Joint 1 - TRANSLATIONAL Sensor Translational MAG DXDY',
    value           = 0.001,
    error           = 1e-05,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'SQRT(DX(30106160, 30101160, 30101160)**2 + DY(30106160, 30101160, 30101160)**2)',
  )

  Bushing_301002 = Bushing(
    id = 301002,
    c  = [2500000.0, 2500000.0, 0.0],
    ct = [5000000.0, 5000000.0, 5000000.0],
    k  = [50000000.0, 50000000.0, 0.0],
    kt = [100000000.0, 100000000.0, 100000000.0],
  )

  Marker_30104170 = Marker(
    id     = 30104170,
    part   = Part_4,
    qp     = Point (0.0035042727749196793, -0.03904374752107413, -0.01596070159239428),
    reuler = Vector (0.0, 3.141592653589793, 3.141592653589793),
  )

  Marker_30106170 = Marker(
    id     = 30106170,
    part   = Part_6,
    qp     = Point (0.0066963552372414515, -0.052686939835622046, 0.06753369269196013),
    reuler = Vector (-3.141592653589793, 1.5707963267948966, -2.4492935982947064e-16),
  )

  Request_25 = Request(
    id           = 25,
    label        = 'Joint 2 - TRANSLATIONAL - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30104170,
    j            = Marker_30106170,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_26 = Request(
    id           = 26,
    label        = 'Joint 2 - TRANSLATIONAL - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30104170,
    j            = Marker_30106170,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_27 = Request(
    id           = 27,
    label        = 'Joint 2 - TRANSLATIONAL - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30104170,
    j            = Marker_30106170,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_28 = Request(
    id           = 28,
    label        = 'Joint 2 - TRANSLATIONAL - FORCE',
    type         = 'FORCE',
    i            = Marker_30104170,
    j            = Marker_30106170,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_301002 = Sensor(
    id              = 301002,
    label           = 'Joint 2 - TRANSLATIONAL Sensor Translational MAG DXDY',
    value           = 0.001,
    error           = 1e-05,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'SQRT(DX(30104170, 30106170, 30106170)**2 + DY(30104170, 30106170, 30106170)**2)',
  )

  Bushing_301003 = Bushing(
    id = 301003,
    c  = [2500000.0, 2500000.0, 0.0],
    ct = [5000000.0, 5000000.0, 5000000.0],
    k  = [50000000.0, 50000000.0, 0.0],
    kt = [100000000.0, 100000000.0, 100000000.0],
  )

  Marker_30105180 = Marker(
    id     = 30105180,
    part   = Part_5,
    qp     = Point (0.05218099999933262, 0.1237640298761, -0.18713200000000024),
    reuler = Vector (3.445092848397696e-16, 1.570796326794897, 1.5707963267949014),
  )

  Marker_30101180 = Marker(
    id     = 30101180,
    part   = Part_1,
    qp     = Point (0.06386956261824168, 0.041752571911941636, -0.08453450000019899),
    reuler = Vector (3.696307845997557e-15, 1.5707963267949108, -3.141592653589793),
  )

  Request_29 = Request(
    id           = 29,
    label        = 'Joint 3 - TRANSLATIONAL - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30105180,
    j            = Marker_30101180,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_30 = Request(
    id           = 30,
    label        = 'Joint 3 - TRANSLATIONAL - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30105180,
    j            = Marker_30101180,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_31 = Request(
    id           = 31,
    label        = 'Joint 3 - TRANSLATIONAL - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30105180,
    j            = Marker_30101180,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_32 = Request(
    id           = 32,
    label        = 'Joint 3 - TRANSLATIONAL - FORCE',
    type         = 'FORCE',
    i            = Marker_30105180,
    j            = Marker_30101180,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_301003 = Sensor(
    id              = 301003,
    label           = 'Joint 3 - TRANSLATIONAL Sensor Translational MAG DXDY',
    value           = 0.001,
    error           = 1e-05,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'SQRT(DX(30105180, 30101180, 30101180)**2 + DY(30105180, 30101180, 30101180)**2)',
  )

  Bushing_301004 = Bushing(
    id = 301004,
    c  = [2500000.0, 2500000.0, 2500000.0],
    ct = [5000000.0, 5000000.0, 0.0],
    k  = [50000000.0, 50000000.0, 50000000.0],
    kt = [100000000.0, 100000000.0, 0.0],
  )

  Marker_30103190 = Marker(
    id     = 30103190,
    part   = Part_3,
    qp     = Point (0.07664976999999999, 0.08206673, 0.0749272),
    reuler = Vector (1.5707963267948966, 1.5707963267949008, -1.5707963267948966),
  )

  Marker_30105190 = Marker(
    id     = 30105190,
    part   = Part_5,
    qp     = Point (0.03183099999900005, 0.13085402987619035, -0.16289699885324643),
    reuler = Vector (0.0, 3.141592653589793, 3.141592653589779),
  )

  Request_33 = Request(
    id           = 33,
    label        = 'Joint 4 - REVOLUTE - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30103190,
    j            = Marker_30105190,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_34 = Request(
    id           = 34,
    label        = 'Joint 4 - REVOLUTE - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30103190,
    j            = Marker_30105190,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_35 = Request(
    id           = 35,
    label        = 'Joint 4 - REVOLUTE - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30103190,
    j            = Marker_30105190,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_36 = Request(
    id           = 36,
    label        = 'Joint 4 - REVOLUTE - FORCE',
    type         = 'FORCE',
    i            = Marker_30103190,
    j            = Marker_30105190,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_301004 = Sensor(
    id              = 301004,
    label           = 'Joint 4 - REVOLUTE Sensor Revolute DM',
    value           = 0.001,
    error           = 1e-05,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'DM(30103190, 30105190)',
  )

  Bushing_301005 = Bushing(
    id = 301005,
    c  = [2500000.0, 2500000.0, 2500000.0],
    ct = [5000000.0, 5000000.0, 0.0],
    k  = [50000000.0, 50000000.0, 50000000.0],
    kt = [100000000.0, 100000000.0, 0.0],
  )

  Marker_30102200 = Marker(
    id     = 30102200,
    part   = Part_2,
    qp     = Point (-0.01013970822120995, 0.16535092334565402, 0.14788299183999076),
    reuler = Vector (3.141592652704202, 5.440781060700528e-06, 1.5663676441561198),
  )

  Marker_30103200 = Marker(
    id     = 30103200,
    part   = Part_3,
    qp     = Point (-1.228853498062843e-06, 0.05476807714700882, 0.07492735079651242),
    reuler = Vector (3.141592653589793, 1.5708017675829133, 0.0),
  )

  Request_37 = Request(
    id           = 37,
    label        = 'Joint 5 - REVOLUTE - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30102200,
    j            = Marker_30103200,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_38 = Request(
    id           = 38,
    label        = 'Joint 5 - REVOLUTE - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30102200,
    j            = Marker_30103200,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_39 = Request(
    id           = 39,
    label        = 'Joint 5 - REVOLUTE - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30102200,
    j            = Marker_30103200,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_40 = Request(
    id           = 40,
    label        = 'Joint 5 - REVOLUTE - FORCE',
    type         = 'FORCE',
    i            = Marker_30102200,
    j            = Marker_30103200,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_301005 = Sensor(
    id              = 301005,
    label           = 'Joint 5 - REVOLUTE Sensor Revolute DM',
    value           = 0.001,
    error           = 1e-05,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'DM(30102200, 30103200)',
  )

  Marker_30303210 = Marker(
    id     = 30303210,
    label  = 'Marker I',
    part   = Part_3,
    qp     = Point (0.07099877114697437, 0.08206672714624791, 0.07492720227060294),
    reuler = Vector (-1.5707963267948948, 1.570796326794892, 1.5707963267948966),
  )

  Marker_30301220 = Marker(
    id     = 30301220,
    label  = 'Marker J',
    part   = Part_1,
    qp     = Point (0.03398356261846213, 0.048842569058280105, -0.1048844977299284),
    reuler = Vector (-1.5707963267948948, 1.570796326794892, 1.5707963267948966),
  )

  Spline_303001 = Spline(
    id                 = 303001,
    label              = 'spline profile',
    x                  = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 30.0],
    y                  = [0.0, -0.17453292519968372, -0.34906585039936744, -0.5235987755990512, -0.6981317007987349, -0.5235987755990512, -0.34906585039936744, -0.17453292519968372, 0.0, 0.17453292519968372, -0.34906585039936744, -0.5235987755990512, -0.6981317007987349, -0.5235987755990512, -0.34906585039936744, 0.17453292519968372, 0.0, 0.0, 0.17453292519968372, -0.34906585039936744, -0.5235987755990512, -0.6981317007987349, -0.5235987755990512, -0.34906585039936744],
    linear_extrapolate = True,
  )

  Variable_30300100 = Variable(
    id       = 30300100,
    label    = 'Motor apsom - Angular Velocity',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'WZ(30303210, 30301220, 30301220)',
  )

  Variable_30300200 = Variable(
    id       = 30300200,
    label    = 'Motor apsom- Angular Acceleration',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'WDTZ(30303210, 30301220, 30301220, 30301220)',
  )

  Variable_30300300 = Variable(
    id       = 30300300,
    label    = 'Motor apsom - Torque',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'MOTION(303001, 0, 8, 30301220)',
  )

  Variable_30300400 = Variable(
    id       = 30300400,
    label    = 'Motor apsom - Reference Angle',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 303001)',
  )

  Variable_30300500 = Variable(
    id       = 30300500,
    label    = 'Motor apsom - Angular Displacement',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'AZ (30303210, 30301220)',
  )

  Poutput_30300100 = Poutput(
    id        = 30300100,
    label     = 'Motor apsom - Plant Outputs',
    variables = [Variable_30300500,Variable_30300100,Variable_30300200,Variable_30300300,Variable_30300400],
  )

  Variable_30300600 = Variable(
    id       = 30300600,
    label    = 'Motor apsom - Command Signal',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Variable_30300700 = Variable(
    id       = 30300700,
    label    = 'Motor apsom - Override Inspire Motion Controller',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Pinput_30300200 = Pinput(
    id        = 30300200,
    label     = 'Motor apsom - Plant Inputs',
    variables = [Variable_30300600,Variable_30300700,Variable_30300300],
  )

  Request_41 = Request(
    id           = 41,
    label        = 'Motor apsom - Kinematic Output',
    type         = 'EXPRESSION',
    f2           = 'AZ (30303210, 30301220)',
    f3           = 'WZ(30303210, 30301220, 30301220)',
    f4           = 'WDTZ(30303210, 30301220, 30301220, 30301220)',
    f6           = '(VARVAL(30300200)-DELAY(VARVAL(30300200),0.001,0))/0.001',
    cnames       = ['', 'Angular_Displacement', 'Angular_Velocity', 'Angular_Acceleration', '', 'Angular_Jerk', '', ''],
    results_name = 'kinematic_output',
  )

  Request_42 = Request(
    id           = 42,
    label        = 'Motor apsom - Power Output',
    type         = 'EXPRESSION',
    f2           = 'VARVAL(30300100)*VARVAL(30300300)',
    cnames       = ['', 'Power', '', '', '', '', '', ''],
    results_name = 'power_output',
  )

  Motion_303001 = Motion(
    id        = 303001,
    label     = 'Motor Constraint',
    i         = Marker_30303210,
    j         = Marker_30301220,
    direction = 'B3',
    icdisp    = 0.0,
    icvel     = 0.0,
    function  = 'IF(VARVAL(30300700):0,STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 303001),VARVAL(30300600))',
  )

  Request_43 = Request(
    id           = 43,
    label        = 'Motor apsom - Output',
    type         = 'EXPRESSION',
    f2           = 'MOTION(303001, 0, 8, 30301220)',
    f3           = 'MOTION(303001, 0, 5, 0)',
    f6           = 'MOTION(303001, 0, 6, 0)',
    f7           = 'MOTION(303001, 0, 7, 0)',
    f8           = 'MOTION(303001, 0, 8, 0)',
    cnames       = ['', 'Torque', 'TM', '', '', 'TX', 'TY', 'TZ'],
    results_name = 'output',
  )

  Sensor_303006 = Sensor(
    id              = 303006,
    label           = 'Motor_apsom Sensor Motor Orientation',
    value           = 0.2617993877991494,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'SQRT(AX(30303210, 30301220)**2+AY(30303210, 30301220)**2)',
  )

  Marker_30502230 = Marker(
    id     = 30502230,
    label  = 'Marker I',
    part   = Part_2,
    qp     = Point (-0.010139708221209909, 0.16535085344730577, 0.13503589184013662),
    reuler = Vector (3.141592609810639, 5.440781060700528e-06, 1.5663676870496828),
  )

  Marker_30503240 = Marker(
    id     = 30503240,
    label  = 'Marker J',
    part   = Part_3,
    qp     = Point (-1.2288534985624433e-06, 0.04192097714715467, 0.07492742069486025),
    reuler = Vector (-3.141592653588642, 1.5708017675826749, 6.265766677367063e-18),
  )

  Spline_305002 = Spline(
    id                 = 305002,
    label              = 'spline profile',
    x                  = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 30.0],
    y                  = [0.0, 0.6981317007987349, 0.5235987755990512, 0.34906585039936744, 0.17453292519968372, 0.0, 0.0, 0.6981317007987349, 0.5235987755990512, 0.34906585039936744, 0.17453292519968372, 0.0, 0.0, 0.6981317007987349, 0.5235987755990512, 0.34906585039936744, 0.17453292519968372, 0.0, 0.0, 0.6981317007987349, 0.5235987755990512, 0.34906585039936744, 0.17453292519968372, 0.0],
    linear_extrapolate = True,
  )

  Variable_30500800 = Variable(
    id       = 30500800,
    label    = 'Motor bposm - Angular Velocity',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'WZ(30502230, 30503240, 30503240)',
  )

  Variable_30500900 = Variable(
    id       = 30500900,
    label    = 'Motor bposm- Angular Acceleration',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'WDTZ(30502230, 30503240, 30503240, 30503240)',
  )

  Variable_30501000 = Variable(
    id       = 30501000,
    label    = 'Motor bposm - Torque',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'MOTION(305002, 0, 8, 30503240)',
  )

  Variable_30501100 = Variable(
    id       = 30501100,
    label    = 'Motor bposm - Reference Angle',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 305002)',
  )

  Variable_30501200 = Variable(
    id       = 30501200,
    label    = 'Motor bposm - Angular Displacement',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'AZ (30502230, 30503240)',
  )

  Poutput_30500300 = Poutput(
    id        = 30500300,
    label     = 'Motor bposm - Plant Outputs',
    variables = [Variable_30501200,Variable_30500800,Variable_30500900,Variable_30501000,Variable_30501100],
  )

  Variable_30501300 = Variable(
    id       = 30501300,
    label    = 'Motor bposm - Command Signal',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Variable_30501400 = Variable(
    id       = 30501400,
    label    = 'Motor bposm - Override Inspire Motion Controller',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Pinput_30500400 = Pinput(
    id        = 30500400,
    label     = 'Motor bposm - Plant Inputs',
    variables = [Variable_30501300,Variable_30501400,Variable_30501000],
  )

  Request_44 = Request(
    id           = 44,
    label        = 'Motor bposm - Kinematic Output',
    type         = 'EXPRESSION',
    f2           = 'AZ (30502230, 30503240)',
    f3           = 'WZ(30502230, 30503240, 30503240)',
    f4           = 'WDTZ(30502230, 30503240, 30503240, 30503240)',
    f6           = '(VARVAL(30500900)-DELAY(VARVAL(30500900),0.001,0))/0.001',
    cnames       = ['', 'Angular_Displacement', 'Angular_Velocity', 'Angular_Acceleration', '', 'Angular_Jerk', '', ''],
    results_name = 'kinematic_output',
  )

  Request_45 = Request(
    id           = 45,
    label        = 'Motor bposm - Power Output',
    type         = 'EXPRESSION',
    f2           = 'VARVAL(30500800)*VARVAL(30501000)',
    cnames       = ['', 'Power', '', '', '', '', '', ''],
    results_name = 'power_output',
  )

  Motion_305002 = Motion(
    id        = 305002,
    label     = 'Motor Constraint',
    i         = Marker_30502230,
    j         = Marker_30503240,
    direction = 'B3',
    icdisp    = 0.0,
    icvel     = 0.0,
    function  = 'IF(VARVAL(30501400):0,STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 305002),VARVAL(30501300))',
  )

  Request_46 = Request(
    id           = 46,
    label        = 'Motor bposm - Output',
    type         = 'EXPRESSION',
    f2           = 'MOTION(305002, 0, 8, 30503240)',
    f3           = 'MOTION(305002, 0, 5, 0)',
    f6           = 'MOTION(305002, 0, 6, 0)',
    f7           = 'MOTION(305002, 0, 7, 0)',
    f8           = 'MOTION(305002, 0, 8, 0)',
    cnames       = ['', 'Torque', 'TM', '', '', 'TX', 'TY', 'TZ'],
    results_name = 'output',
  )

  Joint_305006 = Joint(
    id    = 305006,
    label = 'Centerline',
    type  = 'REVOLUTE',
  )

  Marker_30502231 = Marker(
    id     = 30502231,
    part   = Part_2,
    qp     = Point (-0.010139708221209909, 0.16535085344730577, 0.13503589184013662),
    reuler = Vector (3.141592609810639, 5.440781060700528e-06, 1.5663676870496828),
  )

  Marker_30503241 = Marker(
    id     = 30503241,
    part   = Part_3,
    qp     = Point (-1.2288534985624433e-06, 0.04192097714715467, 0.07492742069486025),
    reuler = Vector (-3.141592653588642, 1.5708017675826749, 6.265766677367063e-18),
  )

  Request_47 = Request(
    id           = 47,
    label        = 'Motor bposm - Centerline - DISPLACEMENT',
    type         = 'DISPLACEMENT',
    i            = Marker_30502231,
    j            = Marker_30503241,
    rm           = Marker_30101010,
    cnames       = ['MAG', 'X', 'Y', 'Z', '', 'PSI', 'THETA', 'PHI'],
    results_name = 'DISPLACEMENT',
  )

  Request_48 = Request(
    id           = 48,
    label        = 'Motor bposm - Centerline - VELOCITY',
    type         = 'VELOCITY',
    i            = Marker_30502231,
    j            = Marker_30503241,
    rm           = Marker_30101010,
    cnames       = ['VM', 'VX', 'VY', 'VZ', 'WM', 'WX', 'WY', 'WZ'],
    results_name = 'VELOCITY',
  )

  Request_49 = Request(
    id           = 49,
    label        = 'Motor bposm - Centerline - ACCELERATION',
    type         = 'ACCELERATION',
    i            = Marker_30502231,
    j            = Marker_30503241,
    rm           = Marker_30101010,
    cnames       = ['ACCM', 'ACCX', 'ACCY', 'ACCZ', 'WDTM', 'WDTX', 'WDTY', 'WDTZ'],
    results_name = 'ACCELERATION',
  )

  Request_50 = Request(
    id           = 50,
    label        = 'Motor bposm - Centerline - FORCE',
    type         = 'FORCE',
    i            = Marker_30502231,
    j            = Marker_30503241,
    rm           = Marker_30101010,
    cnames       = ['FM', 'FX', 'FY', 'FZ', 'TM', 'TX', 'TY', 'TZ'],
    results_name = 'FORCE',
  )

  Sensor_305007 = Sensor(
    id              = 305007,
    label           = 'Motor_bposm Sensor Motor Orientation',
    value           = 0.2617993877991494,
    operator        = 'GE',
    halt            = True,
    sensor_function = 'SQRT(AX(30502230, 30503240)**2+AY(30502230, 30503240)**2)',
  )

  Marker_30706250 = Marker(
    id     = 30706250,
    label  = 'Marker I',
    part   = Part_6,
    qp     = Point (0.07508195087351069, 0.07619806016462034, 0.04527658575036431),
    reuler = Vector (-1.570796326794896, 1.5707963267948972, -2.22044604925031e-16),
  )

  Marker_30701260 = Marker(
    id     = 30701260,
    label  = 'Marker J',
    part   = Part_1,
    qp     = Point (0.06673756261824344, -0.01982542810608806, -0.01568450000150845),
    reuler = Vector (-1.5707963267948961, 1.5707963267948961, 1.5707963267948966),
  )

  Spline_307003 = Spline(
    id                 = 307003,
    label              = 'spline profile',
    x                  = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 30.0],
    y                  = [0.0, 0.007, 0.006, 0.005, 0.0, 0.007, 0.006, 0.005, 0.0, 0.007, 0.006, 0.005, 0.0, 0.007, 0.006, 0.005, 0.0, 0.007, 0.006, 0.005, 0.009, 0.001],
    linear_extrapolate = True,
  )

  Variable_30701500 = Variable(
    id       = 30701500,
    label    = 'Actuator xpm - Velocity',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'VZ(30706250, 30701260, 30701260, 30701260)',
  )

  Variable_30701600 = Variable(
    id       = 30701600,
    label    = 'Actuator xpm- Acceleration',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'ACCZ(30706250, 30701260, 30701260, 30701260)',
  )

  Variable_30701700 = Variable(
    id       = 30701700,
    label    = 'Actuator xpm - Force',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'MOTION(307003, 0, 4, 30701260)',
  )

  Variable_30701800 = Variable(
    id       = 30701800,
    label    = 'Actuator xpm - Reference Displacement',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 307003)',
  )

  Variable_30701900 = Variable(
    id       = 30701900,
    label    = 'Actuator xpm - Travel',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'DZ(30706250, 30701260, 30701260)-0',
  )

  Poutput_30700500 = Poutput(
    id        = 30700500,
    label     = 'Actuator xpm - Plant Outputs',
    variables = [Variable_30701900,Variable_30701500,Variable_30701600,Variable_30701700,Variable_30701800],
  )

  Variable_30702000 = Variable(
    id       = 30702000,
    label    = 'Actuator xpm - Command Signal',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Variable_30702100 = Variable(
    id       = 30702100,
    label    = 'Actuator xpm - Override Inspire Motion Controller',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Pinput_30700600 = Pinput(
    id        = 30700600,
    label     = 'Actuator xpm - Plant Inputs',
    variables = [Variable_30702000,Variable_30702100,Variable_30701700],
  )

  Request_51 = Request(
    id           = 51,
    label        = 'Actuator xpm - Kinematic Output',
    type         = 'EXPRESSION',
    f2           = 'DZ(30706250, 30701260, 30701260)-0',
    f3           = 'VZ(30706250, 30701260, 30701260, 30701260)',
    f4           = 'ACCZ(30706250, 30701260, 30701260, 30701260)',
    f6           = '(VARVAL(30701600)-DELAY(VARVAL(30701600),0.001,0))/0.001',
    cnames       = ['', 'Displacement', 'Velocity', 'Acceleration', '', 'Jerk', '', ''],
    results_name = 'kinematic_output',
  )

  Request_52 = Request(
    id           = 52,
    label        = 'Actuator xpm - Power Output',
    type         = 'EXPRESSION',
    f2           = 'VARVAL(30701500)*VARVAL(30701700)',
    cnames       = ['', 'Power', '', '', '', '', '', ''],
    results_name = 'power_output',
  )

  Motion_307003 = Motion(
    id        = 307003,
    label     = 'Actuator Constraint',
    i         = Marker_30706250,
    j         = Marker_30701260,
    direction = 'Z',
    icdisp    = 0.0,
    icvel     = 0.0,
    function  = 'IF(VARVAL(30702100):0,STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 307003),VARVAL(30702000))',
  )

  Request_53 = Request(
    id           = 53,
    label        = 'Actuator xpm - Output',
    type         = 'EXPRESSION',
    f2           = 'MOTION(307003, 0, 4, 30701260)',
    f3           = 'MOTION(307003, 0, 1, 0)',
    f6           = 'MOTION(307003, 0, 2, 0)',
    f7           = 'MOTION(307003, 0, 3, 0)',
    f8           = 'MOTION(307003, 0, 4, 0)',
    cnames       = ['', 'Force', 'FM', '', '', 'FX', 'FY', 'FZ'],
    results_name = 'output',
  )

  Marker_30905270 = Marker(
    id     = 30905270,
    label  = 'Marker I',
    part   = Part_5,
    qp     = Point (-0.042169000000999934, 0.15587921987518996, -0.1544999820299604),
    reuler = Vector (1.6767769143899575e-15, 1.570796326794897, 1.5707963267949014),
  )

  Marker_30901280 = Marker(
    id     = 30901280,
    label  = 'Marker J',
    part   = Part_1,
    qp     = Point (0.031237544648201276, 0.07386776191103286, -0.17888450000053094),
    reuler = Vector (3.7363274867192736e-15, 1.5707963267949094, -3.141592653589793),
  )

  Spline_309004 = Spline(
    id                 = 309004,
    label              = 'spline profile',
    x                  = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 30.0],
    y                  = [0.0, 0.006, 0.006, 0.0, 0.008, 0.006, 0.006, 0.0, 0.0, 0.006, 0.006, 0.008, 0.008, 0.006, 0.006, 0.0, 0.0, 0.006, 0.006, 0.008, 0.008, 0.006],
    linear_extrapolate = True,
  )

  Variable_30902200 = Variable(
    id       = 30902200,
    label    = 'Actuator ypm - Velocity',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'VZ(30905270, 30901280, 30901280, 30901280)',
  )

  Variable_30902300 = Variable(
    id       = 30902300,
    label    = 'Actuator ypm- Acceleration',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'ACCZ(30905270, 30901280, 30901280, 30901280)',
  )

  Variable_30902400 = Variable(
    id       = 30902400,
    label    = 'Actuator ypm - Force',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'MOTION(309004, 0, 4, 30901280)',
  )

  Variable_30902500 = Variable(
    id       = 30902500,
    label    = 'Actuator ypm - Reference Displacement',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 309004)',
  )

  Variable_30902600 = Variable(
    id       = 30902600,
    label    = 'Actuator ypm - Travel',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'DZ(30905270, 30901280, 30901280)-0',
  )

  Poutput_30900700 = Poutput(
    id        = 30900700,
    label     = 'Actuator ypm - Plant Outputs',
    variables = [Variable_30902600,Variable_30902200,Variable_30902300,Variable_30902400,Variable_30902500],
  )

  Variable_30902700 = Variable(
    id       = 30902700,
    label    = 'Actuator ypm - Command Signal',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Variable_30902800 = Variable(
    id       = 30902800,
    label    = 'Actuator ypm - Override Inspire Motion Controller',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Pinput_30900800 = Pinput(
    id        = 30900800,
    label     = 'Actuator ypm - Plant Inputs',
    variables = [Variable_30902700,Variable_30902800,Variable_30902400],
  )

  Request_54 = Request(
    id           = 54,
    label        = 'Actuator ypm - Kinematic Output',
    type         = 'EXPRESSION',
    f2           = 'DZ(30905270, 30901280, 30901280)-0',
    f3           = 'VZ(30905270, 30901280, 30901280, 30901280)',
    f4           = 'ACCZ(30905270, 30901280, 30901280, 30901280)',
    f6           = '(VARVAL(30902300)-DELAY(VARVAL(30902300),0.001,0))/0.001',
    cnames       = ['', 'Displacement', 'Velocity', 'Acceleration', '', 'Jerk', '', ''],
    results_name = 'kinematic_output',
  )

  Request_55 = Request(
    id           = 55,
    label        = 'Actuator ypm - Power Output',
    type         = 'EXPRESSION',
    f2           = 'VARVAL(30902200)*VARVAL(30902400)',
    cnames       = ['', 'Power', '', '', '', '', '', ''],
    results_name = 'power_output',
  )

  Motion_309004 = Motion(
    id        = 309004,
    label     = 'Actuator Constraint',
    i         = Marker_30905270,
    j         = Marker_30901280,
    direction = 'Z',
    icdisp    = 0.0,
    icvel     = 0.0,
    function  = 'IF(VARVAL(30902800):0,STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 309004),VARVAL(30902700))',
  )

  Request_56 = Request(
    id           = 56,
    label        = 'Actuator ypm - Output',
    type         = 'EXPRESSION',
    f2           = 'MOTION(309004, 0, 4, 30901280)',
    f3           = 'MOTION(309004, 0, 1, 0)',
    f6           = 'MOTION(309004, 0, 2, 0)',
    f7           = 'MOTION(309004, 0, 3, 0)',
    f8           = 'MOTION(309004, 0, 4, 0)',
    cnames       = ['', 'Force', 'FM', '', '', 'FX', 'FY', 'FZ'],
    results_name = 'output',
  )

  Marker_31104290 = Marker(
    id     = 31104290,
    label  = 'Marker I',
    part   = Part_4,
    qp     = Point (0.017989868411262495, -0.042792854443481645, -0.04858070159236291),
    reuler = Vector (0.0, 3.141592653589793, 3.141592653589793),
  )

  Marker_31101300 = Marker(
    id     = 31101300,
    label  = 'Marker J',
    part   = Part_1,
    qp     = Point (0.012837562618317012, -0.001317428086899712, 0.08058049999876529),
    reuler = Vector (0.0, 3.141592653589793, 3.141592653589793),
  )

  Spline_311005 = Spline(
    id                 = 311005,
    label              = 'spline profile',
    x                  = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 30.0],
    y                  = [0.0, 0.008, 0.006, 0.005, 0.002, 0.003, 0.004, 0.007, 0.0, 0.008, 0.006, 0.005, 0.002, 0.003, 0.004, 0.007, 0.0, 0.008, 0.006, 0.005, 0.002, 0.003, 0.004, 0.007],
    linear_extrapolate = True,
  )

  Variable_31102900 = Variable(
    id       = 31102900,
    label    = 'Actuator zpm - Velocity',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'VZ(31104290, 31101300, 31101300, 31101300)',
  )

  Variable_31103000 = Variable(
    id       = 31103000,
    label    = 'Actuator zpm- Acceleration',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'ACCZ(31104290, 31101300, 31101300, 31101300)',
  )

  Variable_31103100 = Variable(
    id       = 31103100,
    label    = 'Actuator zpm - Force',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'MOTION(311005, 0, 4, 31101300)',
  )

  Variable_31103200 = Variable(
    id       = 31103200,
    label    = 'Actuator zpm - Reference Displacement',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 311005)',
  )

  Variable_31103300 = Variable(
    id       = 31103300,
    label    = 'Actuator zpm - Travel',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = 'DZ(31104290, 31101300, 31101300)-0',
  )

  Poutput_31100900 = Poutput(
    id        = 31100900,
    label     = 'Actuator zpm - Plant Outputs',
    variables = [Variable_31103300,Variable_31102900,Variable_31103000,Variable_31103100,Variable_31103200],
  )

  Variable_31103400 = Variable(
    id       = 31103400,
    label    = 'Actuator zpm - Command Signal',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Variable_31103500 = Variable(
    id       = 31103500,
    label    = 'Actuator zpm - Override Inspire Motion Controller',
    penalty  = 100.0,
    penalty1 = 100.0,
    function = '0',
  )

  Pinput_31101000 = Pinput(
    id        = 31101000,
    label     = 'Actuator zpm - Plant Inputs',
    variables = [Variable_31103400,Variable_31103500,Variable_31103100],
  )

  Request_57 = Request(
    id           = 57,
    label        = 'Actuator zpm - Kinematic Output',
    type         = 'EXPRESSION',
    f2           = 'DZ(31104290, 31101300, 31101300)-0',
    f3           = 'VZ(31104290, 31101300, 31101300, 31101300)',
    f4           = 'ACCZ(31104290, 31101300, 31101300, 31101300)',
    f6           = '(VARVAL(31103000)-DELAY(VARVAL(31103000),0.001,0))/0.001',
    cnames       = ['', 'Displacement', 'Velocity', 'Acceleration', '', 'Jerk', '', ''],
    results_name = 'kinematic_output',
  )

  Request_58 = Request(
    id           = 58,
    label        = 'Actuator zpm - Power Output',
    type         = 'EXPRESSION',
    f2           = 'VARVAL(31102900)*VARVAL(31103100)',
    cnames       = ['', 'Power', '', '', '', '', '', ''],
    results_name = 'power_output',
  )

  Motion_311005 = Motion(
    id        = 311005,
    label     = 'Actuator Constraint',
    i         = Marker_31104290,
    j         = Marker_31101300,
    direction = 'Z',
    icdisp    = 0.0,
    icvel     = 0.0,
    function  = 'IF(VARVAL(31103500):0,STEP5(TIME,0,0,0.05,1)*0.0*STEP5(TIME,0.0,1,0.05,0)+STEP5(TIME,0.0,0,0.05,1)*LINSPL(TIME, 0, 311005),VARVAL(31103400))',
  )

  Request_59 = Request(
    id           = 59,
    label        = 'Actuator zpm - Output',
    type         = 'EXPRESSION',
    f2           = 'MOTION(311005, 0, 4, 31101300)',
    f3           = 'MOTION(311005, 0, 1, 0)',
    f6           = 'MOTION(311005, 0, 2, 0)',
    f7           = 'MOTION(311005, 0, 3, 0)',
    f8           = 'MOTION(311005, 0, 4, 0)',
    cnames       = ['', 'Force', 'FM', '', '', 'FX', 'FY', 'FZ'],
    results_name = 'output',
  )

  Marker_30102310 = Marker(
    id     = 30102310,
    part   = Part_2,
    qp     = Point (0.09490742875783673, 0.2019023829508435, 0.1263383032586955),
    reuler = Vector (1.5663676432409923, 1.5708017434874686, -5.440734662032549e-06),
  )

  Marker_30103320 = Marker(
    id   = 30103320,
    part = Part_3,
    qp   = Point (0.037015208528512235, 0.0332241580879678, 0.17981170000053134),
  )

  Marker_30105330 = Marker(
    id     = 30105330,
    part   = Part_5,
    qp     = Point (0.13671549999953192, 0.0820114579641598, -0.12326243738175803),
    reuler = Vector (1.5707963267949112, 1.570796326794892, -1.5707963267949),
  )

  Marker_30106340 = Marker(
    id     = 30106340,
    part   = Part_6,
    qp     = Point (0.00834438825526724, 0.06051356016311188, 0.06510201385645235),
    reuler = Vector (1.2246467991473532e-16, 1.5707963267948968, 1.2246467991473532e-16),
  )

  Marker_30101350 = Marker(
    id   = 30101350,
    part = Part_1,
  )

  Part_2.cm = Marker_30102030
  External_301001.rm = Marker_30102310
  Part_3.cm = Marker_30103050
  External_301002.rm = Marker_30103320
  Part_4.cm = Marker_30104070
  External_302003.rm = Marker_30204080
  External_302004.rm = Marker_30204090
  External_302005.rm = Marker_30204100
  External_302006.rm = Marker_30204110
  Part_5.cm = Marker_30105130
  External_301007.rm = Marker_30105330
  Part_6.cm = Marker_30106150
  External_301008.rm = Marker_30106340
  External_301009.rm = Marker_30101350
  Bushing_301001.i = Marker_30106160
  Bushing_301001.j = Marker_30101160
  Bushing_301002.i = Marker_30104170
  Bushing_301002.j = Marker_30106170
  Bushing_301003.i = Marker_30105180
  Bushing_301003.j = Marker_30101180
  Bushing_301004.i = Marker_30103190
  Bushing_301004.j = Marker_30105190
  Bushing_301005.i = Marker_30102200
  Bushing_301005.j = Marker_30103200
  Joint_305006.i = Marker_30502231
  Joint_305006.j = Marker_30503241

  return Model_0

model = createTheModel ()
model.simulate (type='STATICS', end=0.0, active_contact_iteration=True, dtout=0.0)
model.simulate (type='TRANSIENT', end=30.0, active_contact_iteration=True, dtout=0.03333333333333333)
