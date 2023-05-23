import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { ChakraProvider, Tab, TabList, TabPanel, TabPanels, Tabs } from '@chakra-ui/react';
import '../../app.scss';
import Layout from './layout/Layout';
import Box from './box/Box';
import theme from './theme';
import Split from 'react-split';
import Canvas from '../panels/canvas/Canvas';
import App, { AppContext } from '../../app/App';
import useInitApp from '../panels/canvas/hooks/useInitApp';
import LayerPanel from '../../panels/layer/ui/components/LayerPanel';
import Toolbar from '@/panels/toolbar/ui/Toolbar';
import SettingsPanel from '@/panels/settings/SettingsPanel';
import ToolOptionsPanel from '@/panels/tool_options/ui/ToolOptionsPanel';
import { Provider } from 'react-redux';
import { store } from '@/store';
import SceneViewer from '@/panels/scene_viewer/SceneViewer';
import KeyboardHandler from '@/services/keyboard/KeyboardHandler';
import { editor } from '@/services/editor/Editor';
import ToolEventListener from '@/panels/toolbar/ToolEventListener';

const AppContainer = () => {
  const [canvasContainer, setCanvasContainer] = useState<HTMLCanvasElement | undefined>();

  console.log('app container runs');

  const canvasRef = useCallback((node: HTMLCanvasElement) => node && setCanvasContainer(node), []);

  const app: App = useMemo(
    () => ({
      editorApi: editor,
      editorEvents: window.EditorEvents,
      keyboardHandler: new KeyboardHandler(),
    }),
    [],
  );

  useInitApp(app, canvasContainer);

  useEffect(() => {
    const toolEventListener = new ToolEventListener(app.editorApi);
    toolEventListener.listen(window.EditorEvents);

    /* code to prevent emscripten compiled code from eating key input */
    window.addEventListener(
      'keydown',
      function (event) {
        app.keyboardHandler.emitKeyDown(event);
        event.stopImmediatePropagation();
      },
      true,
    );

    window.addEventListener(
      'keyup',
      function (event) {
        event.stopImmediatePropagation();
      },
      true,
    );
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <ChakraProvider theme={theme} cssVarsRoot="body">
      <Provider store={store}>
        <AppContext.Provider value={app}>
          <Layout
            header={
              <Box
                borderBottom="1px solid"
                borderColor="gray.600"
                display="flex"
                justifyContent="space-between"
                height="40px"
                paddingInline="1"
                paddingBlock="1"
              >
                <SettingsPanel />
              </Box>
            }
            footer={<Box bgColor="orange.400" height="40px"></Box>}
          >
            <Box width="50px">
              <Toolbar />
            </Box>
            <Split className="split" direction="horizontal" sizes={[75, 25]}>
              <Canvas ref={canvasRef} />
              <Split className="split-vertical" direction="vertical" sizes={[50, 50]}>
                <Box overflowY="auto">
                  <LayerPanel />
                </Box>
                <Tabs display="flex" flexDir="column" isLazy>
                  <TabList>
                    <Tab>Options</Tab>
                    <Tab>3D Viewer</Tab>
                  </TabList>
                  <TabPanels alignItems="stretch" display="flex" flex="1">
                    <TabPanel flex="1">
                      <ToolOptionsPanel />
                    </TabPanel>
                    <TabPanel display="flex" flex="1">
                      <SceneViewer />
                    </TabPanel>
                  </TabPanels>
                </Tabs>
              </Split>
            </Split>
          </Layout>
        </AppContext.Provider>
      </Provider>
    </ChakraProvider>
  );
};

export default AppContainer;
