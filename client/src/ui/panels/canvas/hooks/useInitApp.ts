import { initFrames } from '@/features/frame/state/frameSlice';
import { initSettings } from '@/features/settings/state/settingsSlice';
import { initTools } from '@/features/tool/state/toolSlice';
import { initLayers } from '@/panels/layer/state/layerSlice';
import { store } from '@/store';
import { App } from '../../../../app/App';
import DependencyInjector from '../../../../app/DependencyInjector';
import { useEffect, useRef, useState } from 'react';

const useInitApp = (appContext: App, canvasNode?: HTMLCanvasElement) => {
  const [isModuleInitialized, setIsModuleInitialized] = useState(false);

  const dependencyInjector = useRef(new DependencyInjector(appContext));

  // eslint-disable-next-line react-hooks/exhaustive-deps
  useEffect(() => {
    appContext.editorApi.canvas = canvasNode;
    if (window?.Module?.isRuntimeInitialized && !isModuleInitialized) {
      setIsModuleInitialized(true);
      dependencyInjector.current.init();

      // store.dispatch(initFrames(editorApi));
      // store.dispatch(initLayers(editorApi));
      // store.dispatch(initTools(editorApi));
      // store.dispatch(initSettings(editorApi));
    }
  });

  return {
    isModuleInitialized,
  };
};

export default useInitApp;
