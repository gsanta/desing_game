import { createSlice, PayloadAction } from '@reduxjs/toolkit';
import { RootState } from '../../../store';
import Frame from './Frame';

interface FrameState {
  count: number;
  frames: Frame[];
  activeIndex: number;
}

const initialState: FrameState = {
  count: 1,
  frames: [],
  activeIndex: 0,
};

export const frameSlice = createSlice({
  name: 'frame',
  initialState,
  reducers: {
    setActiveIndex: (state, action: PayloadAction<number>) => {
      state.activeIndex = action.payload;
    },

    addFrame: (state) => {
      state.count += 1;
    },
    removeFrame: (state) => {
      state.count -= 1;
    },
    initFrames: (state) => {
      state.count = 10;
    },
  },
});

export const { addFrame, initFrames, removeFrame } = frameSlice.actions;

export const selectCount = (state: RootState) => state.frame.count;

export default frameSlice.reducer;
