vtk_add_test_cxx(vtkPVVTKExtensionsConduitCxxTests tests
  TestConduitSource.cxx,NO_VALID)

vtk_test_cxx_executable(vtkPVVTKExtensionsConduitCxxTests tests)
