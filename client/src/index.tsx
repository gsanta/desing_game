import React from 'react';
import { createRoot, Root } from 'react-dom/client';
import App from './core/App';
import ModuleManager from './core/ModuleManager';
import Editor from './services/api/Editor';
import CanvasEventHandler from './services/canvas/CanvasEventHandler';
import LifeCycleEventHandler from './services/core/LifeCycleEventHandler';
import WindowHandler from './services/core/WindowHandler';
import KeyboardHandler from './services/keyboard/KeyboardHandler';
import Settings from './services/Settings';
import ToolStore from './services/tool/ToolStore';
import AppContainer from './ui/components/AppContainer';
import LayerHandler from './ui/panels/layer/LayerHandler';

window.CanvasEventHandler = new CanvasEventHandler();

const editor = new Editor();
const app: App = {
  editorApi: editor,
  toolStore: new ToolStore(),
  editorStore: new Settings(editor),
  canvasEventHandler: window.CanvasEventHandler as CanvasEventHandler,
  lifeCycleEventHandler: new LifeCycleEventHandler(),
  moduleManager: new ModuleManager(),
  keyboardHandler: new KeyboardHandler(),
  windowHandler: new WindowHandler(),
  layerHandler: new LayerHandler(editor),
};

let root: Root;

function renderApp() {
  const container = document.getElementById('root');

  if (!container) {
    throw new Error('Container does not exists');
  }

  if (!root) {
    root = createRoot(container);
  }

  root.render(<AppContainer app={app} />);
}

renderApp();

window.renderApp = renderApp;
