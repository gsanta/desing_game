/* eslint-disable no-var */

import Editor from '@/features/editor/Editor';
import EditorEvents from '@/features/editor/EditorEvents';
import EditorRuntime from '@/features/editor/EditorRuntime';
import EditorListener from '@/services/editor/EditorListener';

declare global {
  function renderApp(): void;

  var Module: EditorRuntime;

  var EditorEvents: EditorEvents;
  var EditorListener: EditorListener;
}

export {};
