#@format=datatools::configuration::variant
#@format.version=1.0
#@organization=snemo
#@application=falaise

[registry="geometry"]
layout = "Basic"
layout/if_basic/magnetic_field = false
layout/if_basic/source_layout = "Basic"
layout/if_basic/source_layout/if_basic/thickness = 250 um
layout/if_basic/source_layout/if_basic/material = "Se82"
layout/if_basic/source_calibration = true
layout/if_basic/source_calibration/is_active/type = "SDS"
layout/if_basic/source_calibration/is_active/type/if_sds/track0 = true
layout/if_basic/source_calibration/is_active/type/if_sds/track1 = true
layout/if_basic/source_calibration/is_active/type/if_sds/track2 = true
layout/if_basic/source_calibration/is_active/type/if_sds/track3 = true
layout/if_basic/source_calibration/is_active/type/if_sds/track4 = true
layout/if_basic/source_calibration/is_active/type/if_sds/track5 = true
layout/if_basic/shielding = true
calo_film_thickness = 25 um
tracking_gas_material = "Nemo3"

[registry="vertexes"]
generator = "sds_bi207_calibration_source_all_tracks"

[registry="primary_events"]
generator = "calibBi207"

[registry="simulation"]
physics_mode = "Constructors"
physics_mode/if_constructors/em_model = "standard"
production_cuts = true
output_profile = "all_details"

