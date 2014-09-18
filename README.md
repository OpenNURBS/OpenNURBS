OpenNURBS
=========

OpenNURBS is an open-source NURBS-based geometric modeling library and toolset, 
with meshing and display / output functions. OpenNURBS .nrb_geom files hold
NURBS parametric geometry models and can be used to save and load a working model,
and can be used to create meshes and output to mesh file formats. OpenNURBS will
start as just objects but will eventually support both interactive GUI and API access.

Roadmap for development:
  Phase I:
    1. basis, curve, surface objects, conic sections object
       - node, curve, surface, region objects
    2. save to file, standard mesh format
    3. CV curve instantiation, conversion to NURBS
    4. Curve and Surface offsetting
    5. Extrusion, Offset Extrusion
    6. Display feedback first steps

  Phase II:
    6. Tube Capping
    7. Smoothing
    8. Joining / Filleting extruded tubes
    9. Geometry object primitives and basic operations
    10. Display work 
    11. API rollout


