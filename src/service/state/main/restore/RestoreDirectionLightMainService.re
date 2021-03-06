open StateDataMainType;

open DirectionLightType;

let _restoreTypeArrays =
    (currentDirectionLightRecord, targetDirectionLightRecord) =>
  currentDirectionLightRecord.colors === targetDirectionLightRecord.colors
  &&
  currentDirectionLightRecord.intensities === targetDirectionLightRecord.
                                                intensities ?
    (currentDirectionLightRecord, targetDirectionLightRecord) :
    {
      let (colors, intensities) =
        (
          currentDirectionLightRecord.colors,
          currentDirectionLightRecord.intensities,
        )
        |> RecordDirectionLightMainService.setAllTypeArrDataToDefault(
             currentDirectionLightRecord.index,
           );
      TypeArrayService.fillFloat32ArrayWithFloat32Array(
        (currentDirectionLightRecord.colors, 0),
        (targetDirectionLightRecord.colors, 0),
        Js.Typed_array.Float32Array.length(targetDirectionLightRecord.colors),
      )
      |> ignore;
      TypeArrayService.fillFloat32ArrayWithFloat32Array(
        (currentDirectionLightRecord.intensities, 0),
        (targetDirectionLightRecord.intensities, 0),
        Js.Typed_array.Float32Array.length(
          targetDirectionLightRecord.intensities,
        ),
      )
      |> ignore;
      (currentDirectionLightRecord, targetDirectionLightRecord);
    };

let restore = (currentState, targetState) => {
  let currentDirectionLightRecord =
    RecordDirectionLightMainService.getRecord(currentState);
  let targetDirectionLightRecord =
    RecordDirectionLightMainService.getRecord(targetState);
  let (currentDirectionLightRecord, targetDirectionLightRecord) =
    _restoreTypeArrays(
      currentDirectionLightRecord,
      targetDirectionLightRecord,
    );
  {
    ...targetState,
    directionLightRecord:
      Some({
        ...targetDirectionLightRecord,
        buffer: currentDirectionLightRecord.buffer,
        colors: currentDirectionLightRecord.colors,
        intensities: currentDirectionLightRecord.intensities,
      }),
  };
};