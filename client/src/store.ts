import { configureStore } from '@reduxjs/toolkit';
import frameSlice from './features/frame/state/frameSlice';
import layerSlice from './panels/layer/state/layerSlice';

export const store = configureStore({
  reducer: {
    frame: frameSlice,
    layer: layerSlice,
  },
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;
