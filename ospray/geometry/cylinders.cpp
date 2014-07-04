#undef NDEGBUG

// ospray
#include "cylinders.h"
#include "common/data.h"
#include "common/model.h"
// ispc-generated files
#include "cylinders_ispc.h"

namespace ospray {

  Cylinders::Cylinders()
  {
    this->ispcEquivalent = ispc::Cylinders_create(this);
  }

  void Cylinders::finalize(Model *model) 
  {
    radius            = getParam1f("radius",0.01f);
    materialID        = getParam1i("materialID",0);
    bytesPerCylinder  = getParam1i("bytes_per_cylinder",7*sizeof(float));
    offset_v0         = getParam1i("offset_v0",0);
    offset_v1         = getParam1i("offset_v1",3*sizeof(float));
    offset_radius     = getParam1i("offset_radius",6*sizeof(float));
    offset_materialID = getParam1i("offset_materialID",-1);
    data              = getParamData("cylinders",NULL);
    
    Assert2(data != NULL, "no data specified");
    Assert2(bytesPerCylinder > 0, "no data specified");
    numCylinders = data->numBytes / bytesPerCylinder;
    std::cout << "#osp: creating 'cylinders' geometry, #cylinders = " << numCylinders << std::endl;
    
    ispc::CylindersGeometry_set(getIE(),model->getIE(),
                                data->data,numCylinders,bytesPerCylinder,
                                radius,materialID,
                                offset_v0,offset_v1,offset_radius,offset_materialID);
  }


  OSP_REGISTER_GEOMETRY(Cylinders,cylinders);
}